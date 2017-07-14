// File: wordcounting.c
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description: This is the .c file that contains functions for creating an alphabetized list of words
// from a start and end file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  //for tolower function
#include "wordcounting.h"
#include "bool.h"

//this function creates the linked list from the start input file while alphabetizing it

void Start_CreateAndCount(FILE* input, DList* list){
    char readWord[1000] = " ";  //string to store file input in
    DListNode* readNode = NULL; //pointer to DListNode to store information from file
    DListNode* currNode = NULL; //pointer to store which DListNode to store readNode after
    
    while(fscanf(input, "%s", readWord) != -1){ //loop continues until end of file reached

        strTolower(readWord);   //loop continues until end of file reached
        
        currNode = FindABCLoc(list, readWord);  //find location to add in alphabetized list
        
        if (currNode == NULL){

            readNode = (DListNode*)malloc(sizeof(DListNode));   //allocate memory, check that it has been allocated
			if (readNode == NULL){
				printf("Error, malloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}
            
			DListNodeInit(readNode);   //initialize values for node (allocates memory for char* word)

			readNode->word = (char*)realloc(readNode->word, (strlen(readWord) + 1) * sizeof(char)); //reallocate memory, check that it has been allocated
			if (readNode->word == NULL){
				printf("Error, realloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}
            
            strcpy(readNode->word, readWord);   //copy word to the node and set start count 1
            readNode->startCount = 1;

            
            DListInsertAfter(list, NULL, readNode); //since alphabetizer gave NULL, must insert at head
        }
        else if (strcmp(currNode->word, readWord) == 0){
            currNode->startCount++; //if word is already on list, increase count
        }
        else{
            
            readNode = (DListNode*)malloc(sizeof(DListNode));   //allocate memory, check that it has been allocated
			if (readNode == NULL){
				printf("Error, malloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}
			DListNodeInit(readNode);    //initialize node values (allocates char* word memory)

            readNode->word = (char*)realloc(readNode->word, (strlen(readWord) + 1) * sizeof(char)); //reallocate memory, check that it has been allocated
			if (readNode->word == NULL){
				printf("Error, realloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}

            strcpy(readNode->word, readWord);   //copy word to the node and set start count 1
            readNode->startCount = 1;
            
            DListInsertAfter(list, currNode, readNode); //insert at location given by alphabetizer
        }
    }
}

//this function creates the linked list from the end input file while alphabetizing it

void End_CreateAndCount(FILE* input, DList* list){
    char readWord[1000] = " ";  //string to store file input in
    DListNode* readNode = NULL; //pointer to DListNode to store information from file
    DListNode* currNode = NULL; //pointer to store which DListNode to store readNode after
    
    while(fscanf(input, "%s", readWord) != -1){ //loop continues until end of file reached

        strTolower(readWord);   //loop continues until end of file reached
        
        currNode = FindABCLoc(list, readWord);  //find location to add in alphabetized list
        
        if (currNode == NULL){
			readNode = (DListNode*)malloc(sizeof(DListNode));   //allocate memory, check that it has been allocated
			if (readNode == NULL){
				printf("Error, malloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}
			DListNodeInit(readNode);    //initialize values for node (allocates memory for char* word)

			readNode->word = (char*)realloc(readNode->word, (strlen(readWord) + 1) * sizeof(char)); //reallocate memory, check that it has been allocated
			if (readNode->word == NULL){
				printf("Error, realloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}
            strcpy(readNode->word, readWord);   //copy word to the node and set start count 1
            readNode->endCount = 1;

            
            DListInsertAfter(list, NULL, readNode);  //since alphabetizer gave NULL, must insert at head

        }
        else if (strcmp(currNode->word, readWord) == 0){
            currNode->endCount++;   //if word is already on list, increase count
        }
        else{
            
            readNode = (DListNode*)malloc(sizeof(DListNode));   //allocate memory, check that it has been allocated
			if (readNode == NULL){
				printf("Error, malloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}

			DListNodeInit(readNode);

			readNode->word = (char*)realloc(readNode->word, (strlen(readWord) + 1) * sizeof(char)); //reallocate memory, check that it has been allocated
			if (readNode->word == NULL){
				printf("Error, realloc failed to reserve data.");
				exit(EXIT_FAILURE);
			}
            strcpy(readNode->word, readWord);   //copy word to the node and set start count 1
            readNode->endCount = 1;

            
            DListInsertAfter(list, currNode, readNode); //insert at location given by alphabetizer
        }
    }
}

//This function converts an entire string to lowercase

void strTolower(char* string){
    
    int i = 0;
    char c = ' ';
    
    for (i = 0; strlen(string) > i; i++){   //until reaches end of string, make each character lowercase
        c = tolower(string[i]);
        string[i] = c;
    }
    
    return;
}