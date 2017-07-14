// File: wordcounting.h
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description: This is the header file that contains functions for creating an alphabetized list of words
// from a start and end file

#include "bool.h"
#include "dlist.h"

#ifndef WORDCOUNTING_H
#define WORDCOUNTING_H

//this function creates the linked list from the start input file while alphabetizing it

void Start_CreateAndCount(FILE* input, DList* list);

//this function creates the linked list from the end input file while alphabetizing it

void End_CreateAndCount(FILE* input, DList* list);

//This function converts an entire string to lowercase

void strTolower(char* string);

#endif