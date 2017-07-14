/**************************************************************************************************/

/*
 * File: tempdata.h
 * Author: Brandon Jernigan
 * NetID: brandonjernigan
 * Date: September 15, 2014
 *
 * Description: Declaration of functions for C program that reads an input file, reduces erroneous readings,
 * applies low pass filter, extracts AC trend data, and produces output file with processed data
 */

/**************************************************************************************************/

#include "bool.h"

/**************************************************************************************************/

#ifndef ACTEMPDATA_H
#define ACTEMPDATA_H

/**************************************************************************************************/

#define MinPerDay 1440

/*
 * If you are using a C compiler that supports the C99 standard, it is recommended that 
 * you use the following. As a note, Microsft Visual Studio does not support the C99 standard.
 *
 * static const int MinPerDay = 1440;
 * 
 */
 
/**************************************************************************************************/

/* 
 * Data structure for representing AC temperature readings and status. temperature stores the 
 * temperature reading, valid indicates if the reading is valid, and status indicates if
 * the AC was Off.
 *
 */
typedef struct ACTempData_struct {
   double temperature;
   bool status;
   bool valid;
} ACTempData;

/**************************************************************************************************/

/* Reads tempertures from an input file specified by fileName line-by-line using the format:
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
 * Retruns false if the specified file could not be opened, and true otherwise.
 *
 */
bool ReadTempDataFromFile(ACTempData acTemps[], char *fileName);

/**************************************************************************************************/

/*
 * Remove any erroneous temperature readings. An error temperature reading is defined as a
 * temperature reading that is either more than 5 degrees above or 5 below the temperature 
 * recorded in the previous minute. All erroneous temperature readings should be removed.
 *
 */
void RemoveErroneousData(ACTempData acTemps[]);

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
void LowPassFilter(ACTempData acTemps[]);

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
void TrendExtraction(ACTempData acTemps[]);

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
bool WriteTempDataToFile(ACTempData acTemps[], char *fileName);


/**************************************************************************************************/

#endif

/**************************************************************************************************/
