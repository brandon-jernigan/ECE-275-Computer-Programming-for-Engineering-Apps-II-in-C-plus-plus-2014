// File: dlist.h
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description:

#include "bool.h"

#ifndef DLIST_H
#define DLIST_H

typedef struct DListNode_struct {   //struct for list node storeing a word and a frequency count for two files

	char *word;
	unsigned long startCount;
	unsigned long endCount;
	struct DListNode_struct *next;
	struct DListNode_struct *prev;

} DListNode;

typedef struct DList_struct {   //struct for storing head, tail and size of DListNodes

	int size;
	DListNode *head;
	DListNode *tail;

} DList;

//initializes list

void DListInit(DList* list);

//frees memory of each node and its string, then the list itself

void DListDestroy(DList* list);

//inserts given node after current node given, currNode = NULL inserts at head of list

bool DListInsertAfter(DList* list, DListNode* currNode, DListNode* newNode);

//inserts given node after before node given

bool DListInsertBefore(DList* list, DListNode* currNode, DListNode* newNode);

//search given list for given key word

DListNode* DListSearch(DList* list, char* key);

//find location in alphabetized list of word in given node

DListNode* FindABCLoc(DList* list, char* key);

//remove node from given list

bool DListRemove(DList* list, DListNode* currNode);

//print entire list to screen

void DListPrint(DList* list);

//print entire list to file

void DListFprint(FILE* output, DList* list);

//initialize values for node, allocates memory for char* word

void DListNodeInit(DListNode* node);


#endif