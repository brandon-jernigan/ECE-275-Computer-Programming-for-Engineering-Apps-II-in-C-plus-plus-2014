// File: main.c
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description: This is the main function for a program that takes two input files containing a list of words and finds which 5 words
// increase in frequency the most and which 5 words decrease in frequency the most. This will be carried out by alphebetizing the words
// in a doubly linked list with frequency data, and by sorting through this list to find which words match the stated criteria.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "dlist.h"
#include "wordcounting.h"
#include "trending.h"

int main(int argc, char* argv[])
{
	DList* list = NULL; //list that will store all words from input files
	FILE* input = NULL; //input pointer

    if(argc != 3){                                                // implement when I can use args
        printf("\nUsage: %s startFile endFile \n\n", argv[0]);
        return -1;
    }

	list = (DList*)malloc(sizeof(DList));   //allocate memory, check that it has been allocated
	if (list == NULL){
		printf("Error, malloc failed to reserve data.");
		return -1;
	}

	DListInit(list);


    input = fopen(argv[1], "r"); // open 1st file
	if (input == NULL){
		printf("Could not read file.\n");
		return -1;
	}
    
    Start_CreateAndCount(input, list);  //this function creates the linked list from the start input file while alphabetizing it
    
    fclose(input);
    
    input = fopen(argv[2], "r"); // open 2nd file
    if (input == NULL){
        printf("Could not read file.\n");
        return -1;
    }
    
    End_CreateAndCount(input, list);    //this function creates the linked list from the end input file while alphabetizing it
    
    fclose(input);

    
    trending(list); //this function takes an alphabetized list of words with frequency data and finds the top five that are trending up and down between the input files
    
	DListDestroy(list); //this destroys the entire list
	
	return 0;
}