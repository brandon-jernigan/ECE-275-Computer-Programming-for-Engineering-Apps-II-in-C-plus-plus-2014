/**************************************************************************************************/

/*
 * File: tempdata.c
 * Author: Brandon Jernigan
 * NetID: brandonjernigan
 * Date: September 15, 2014
 *
 * Description: Definition of functions for C program that reads an input file, reduces erroneous readings,
 * applies low pass filter, extracts AC trend data, and produces output file with processed data
 */

/**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "bool.h"
#include "tempdata.h"

/**************************************************************************************************/

/* Reads temperatures from an input file specified by fileName line-by-line using the format:
 *
 *    HH:MM TT.T
 *
 * HH:MM represents the time at which the temperature was recorded and is specific in 24 hour
 * format.
 *
 * TT.T represents the recorded temperature reported in Fahrenheit as a floating point value.
 *
 * The time and temperature will be separated by one or more whitespace characters.
 *
 * All lines that do not exactly match this format will be ignored.
 *
 * Returns false if the specified file could not be opened, and true otherwise.
 *
 */
bool ReadTempDataFromFile(ACTempData acTemps[], char *fileName)
{
	FILE* input = NULL;	//stores file address
	int i = 0;	//iterative variable
	int fscanfReturn = 0;	//stores number of readings returned by fscanf
	int hour = 0;	//stores hour reading
	int min = 0;	//stores minute reading


	input = fopen(fileName, "r");	//opens 2nd command line argument for file reading, 
									//returns false if no file found

	if(input == NULL){		//check for valid file
		return false;
	}

	for (i = 0; i < MinPerDay; i++){	//initializes all temp readings to -1
										//this will flag any missing times
										//because no temp will be outside of
										//0.00 - 99.9 degree range
		acTemps[i].temperature = -1;
	}


	for(i=0;!feof(input); i++){			//Scans file, stores results. 
									//Temperature readings go into acTemps array
									//in slot corresponding to minute of the day.
									//if correct format not found, return error.
		
		fscanfReturn = fscanf(input, "%2d:%2d", &hour, &min);	//read hour and minute reading from file

		if (fscanfReturn != 2){
			if (fscanfReturn == -1){	//-1 means end of file has already been reached, exits function
				if(i == 0){		//-1 on 1st iteration means this file is empty
					printf("Empty File.\n");
					return false;
				}
				return true;
			}
			printf("Incorrect format.\n");
			return false;
		} 
		else if (0 > hour || hour > 23){	//hours must be within acceptable number range
			printf("Incorrect format.\n");
			return false;

		} 
		else if (0 > min || min > 59){	////minutes must be within acceptable number range
			printf("Incorrect format.\n");
			return false;

		} 

		fscanfReturn = fscanf(input, " %4lf", &acTemps[hour * 60 + min].temperature);	//read temperature data from file

		if (fscanfReturn != 1){	//store temperature reading in array slot
			if (fscanfReturn == -1){
				return true;
			}
			printf("Incorrect format 2.\n");												//corresponding to the minute in a day
			return false;

		}
	}

	fclose(input);



   return true;
}

/**************************************************************************************************/

/*
 * Remove any erroneous temperature readings. An error temperature reading is defined as a
 * temperature reading that is either more than 5 degrees above or 5 below the temperature
 * recorded in the previous minute. All erroneous temperature readings should be removed.
 *
 */
void RemoveErroneousData(ACTempData acTemps[])
{
	int i = 0;	//iterative variable
	double difference = 0;	//for calculating the difference between two temperatures

	for(i = 0; i < MinPerDay; i++){		//initialize all acTemps to invalid
		acTemps[i].valid = false;
	}

	for (i = 0; i < MinPerDay; i++){

		if (acTemps[i].temperature != -1){	//-1 was flagged as empty array location
		
			acTemps[i].valid = true;	//1st member in file always valid
			break;
		}
	}

	for(i = 1; i < MinPerDay; i++){	//reads each member of acTemps array, 

		difference = acTemps[i].temperature - acTemps[i-1].temperature;		
									
		if (acTemps[i].temperature != -1){
			if (((difference > -5.0) && (difference < 5.0)) && (acTemps[i - 1].valid == true)){	
											//if previous reading valid and the difference is
											//between +/-5, mark current as valid
				acTemps[i].valid = true;
			}
			else if (acTemps[i - 1].valid == false){	//if previous reading invalid, mark current valid
				acTemps[i].valid = true;
			}
		}
	}


}

/**************************************************************************************************/

/*
 * Applies a low-pass filter to sequences of valid temperature readings for consecutive times.
 * If a non-valid temperature reading is found, the filter should restart at the next valid
 * temperature reading. The following describes the low-pass filter used:
 *
 *    filtered_output(0) = unfiltered_input(0)
 *    filtered_output(n) = 0.9375 * filtered_output(n-1) + 0.0625 * unfiltered_input(n)
 *
 */
void LowPassFilter(ACTempData acTemps[])
{
	int i = 0;	//iterative variable

	for (i = 1; i < MinPerDay; i++){
		if (acTemps[i - 1].valid == true && acTemps[i].valid == true){	//for consecutive valid readings, apply low-pass filter

			acTemps[i].temperature = 0.9375 * acTemps[i - 1].temperature + 0.0625 * acTemps[i].temperature;
		}
	}
}

/**************************************************************************************************/

/*
 * Analyzes the sequence of valid temperatures to determine the state of the AC. If a non-valid
 * temperature reading is found, the trend extraction should restart at the next valid temperature
 * reading. Trend extraction analysis operate as follows:
 *
 * 1. The AC status for the first entry in a sequence of valid reading is always Off.
 *
 * 2. For a valid temperature reading that does not start a sequence:
 *
 *    A. If (1) the previous AC status was Off, (2) the previous temperature is valid, (3) the
 *       current temperature is less than the previous temperature, and (4) the next temperature
 *       is valid and less than the current temperature, then the AC status for the current
 *       temperature will be On. Otherwise, the AC status for the current temperature will be Off.
 *
 *    B. If (1) the previous AC status was On and (2) the current temperature is less than or equal
 *       to the previous temperature, then the AC status for the current temperature will be On.
 *       Otherwise, the AC status for the current temperature will be Off.
 *
 */
void TrendExtraction(ACTempData acTemps[])
{
	int i = 0;

	for (i = 0; i < MinPerDay; i++){	//initialize all AC status readings to off
		acTemps[i].status = false;
	}

	for (i = 1; i < MinPerDay; i++){	//sets AC status to on if data meets following criteria

		if (acTemps[i - 1].valid == true && acTemps[i].valid == true){	//must be two consecutive readings
			switch (acTemps[i - 1].status){		//two criteria available depending on if previous AC status was on or off
				case false:	
					if (i < MinPerDay - 1 && acTemps[i + 1].valid == true){		//if this is not last reading in a sequence of valid readings, or last in the file
						if(acTemps[i - 1].temperature > acTemps[i].temperature && acTemps[i + 1].temperature < acTemps[i].temperature){

							acTemps[i].status = true;	//if AC status was previously off
														//previous temp is be higher, 
														//and following temp is be lower,
														//then AC status is on
						}
					}
					break;
				case true:
					if (acTemps[i - 1].temperature >= acTemps[i].temperature){
					acTemps[i].status = true;	//if AC status was previously on, and previous temp was larger
												//then AC status is on
					}
					break;
			}
		}
	}
}

/**************************************************************************************************/

/* Writes all valid tempertures readings and AC status to an output file specified by fileName
 * using the format:
 *
 *    HH:MM TT.TTT AC
 *
 * HH:MM reports the time at which the temperature was recorded specified in 24 hour format.
 *
 * TT.TTT represents the filtered temperature value in Fahrenheit as a floating point value with
 * three decimal digits of precision.
 *
 * AC reports the determined status of the air conditioner, where a 0 represents the the AC
 * was Off and a 1 represents the AC was On.
 *
 * Each entry is separated by a single tab character (\t).
 *
 * Retruns false if the specified file could not be written to, and true otherwise.
 *
 */
bool WriteTempDataToFile(ACTempData acTemps[], char *fileName)
{
	FILE* output = NULL;	//stores address of output file
	int i = 0;	//iterative variable

	output = fopen(fileName, "w");

	if (output == NULL){	//check for valid file
		return false;
	}

	for (i = 0; i < MinPerDay; i++){	//print all valid readings to file
//		fprintf(output, "%02d:%02d\t%4.3lf\t%d\tV:%d\n", i / 60, i % 60, acTemps[i].temperature, acTemps[i].status, acTemps[i].valid);

		if (acTemps[i].valid == true){
		fprintf(output, "%02d:%02d\t%06.3lf\t%d\n", i / 60, i % 60, acTemps[i].temperature, acTemps[i].status);
		}
	}

	fclose(output);

	return true;
}

/**************************************************************************************************/

