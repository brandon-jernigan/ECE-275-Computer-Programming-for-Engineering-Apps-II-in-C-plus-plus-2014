/**************************************************************************************************/

/*
 * File: main.c
 * Author: Brandon Jernigan
 * NetID: brandonjernigan
 * Date: September 15, 2014
 *
 * Description: Main functionality for C program that reads an input file, reduces erroneous readings,
 * applies low pass filter, extracts AC trend data, and produces output file with processed data
 *
 */

/**************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "bool.h"
#include "tempdata.h"

/**************************************************************************************************/

int
main(int argc, char *argv[])
{
	ACTempData acTemps[MinPerDay];
   
   /*
    * check for the correct number of commandline arguments.  If incorrect
    * provide a simple usage message to the assist the user
    *
    */
	if( argc != 3 ) {
      printf("\nUsage: %s inputFile outputFile \n\n", argv[0]);
      return -1;
	}
	
   if( !ReadTempDataFromFile(acTemps, argv[1]) ) {
      printf("Could not read from input file %s\n", argv[1]);
      return -1;
   }

   RemoveErroneousData(acTemps);
   LowPassFilter(acTemps);
   TrendExtraction(acTemps);
   
   if( !WriteTempDataToFile(acTemps, argv[2]) ) {
      printf("Could not write to output file %s\n", argv[2]);
      return -1;
   }

   printf("Data read, processed, and written to file.\n\n");

	return 0;
}

/**************************************************************************************************/
