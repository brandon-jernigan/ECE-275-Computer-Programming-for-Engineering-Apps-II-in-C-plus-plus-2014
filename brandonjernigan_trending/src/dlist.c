// File: dlist.c
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description: .c file that contains functions for doubly linked list, such as initialize, insert, search, and destroy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "dlist.h"


//initializes list

void DListInit(DList* list){

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return;
}

//frees memory of each node and its string, then the list itself

void DListDestroy(DList* list){

	DListNode* currNode = list->head;
	DListNode* nextNode = NULL;

	while (currNode != NULL){   //traverse list, freeing word, node, and then when done, free list

		nextNode = currNode->next;
		free(currNode->word);
		free(currNode);
		currNode = nextNode;
	}

	free(list);

	return;
}

//inserts given node after current node given, currNode = NULL inserts at head of list

bool DListInsertAfter(DList* list, DListNode* currNode, DListNode* newNode){

	DListNode* nextNode = NULL;
    
    if (list == NULL){
        return false;
    }
    
	if (list->head == NULL){    //if head is null, this is a new list

		list->head = newNode;
		list->tail = newNode;
	}
	else if (currNode == NULL){ //if provided currNode is NULL, insert at head
        
		nextNode = list->head;
		list->head = newNode;
		newNode->next = nextNode;

		if (nextNode != NULL){  //unless this is the end of the list, link next item back to current item
			nextNode->prev = newNode;
		}
		else{
			list->tail = newNode;   //if it is the tail, designate it
		}
	}
	else{                               //otherwise make all linkages for items before and after
		nextNode = currNode->next;
		currNode->next = newNode;
		newNode->prev = currNode;
		newNode->next = nextNode;

		if (nextNode != NULL){
			nextNode->prev = newNode;
		}
		else {
			list->tail = newNode;
		}
	}
	list->size++;   //increment list size for this new item
    
	return true;
}

//inserts given node after before node given

bool DListInsertBefore(DList* list, DListNode* currNode, DListNode* newNode){

	DListNode* tempNode = NULL;

    if (list == NULL){
        return false;
    }
    
	if (list->head == NULL){    //if head is null, this is a new list

		list->head = newNode;
		list->tail = newNode;
	}
	else if (currNode == NULL){ //if provided currNode is NULL, insert at head

		tempNode = list->head;
		list->head = newNode;
		newNode->next = tempNode;

		if (tempNode != NULL){  //unless this is the beginning of the list, link next item back to current item
			tempNode->prev = newNode;
		}
		else{
			list->tail = newNode;
		}
	}
	else{
		tempNode = currNode->prev;   //otherwise make all linkages for items before and after
		currNode->prev = newNode;
		newNode->next = currNode;
		newNode->prev = tempNode;

		if (tempNode != NULL){
			tempNode->next = newNode;
		}
		else {
			list->head = newNode;
		}
	}
	list->size++;   //increment list size for this new item
    
	return true;

}

//search given list for given key word

DListNode* DListSearch(DList* list, char* key){
    DListNode* currNode = list->head;
    
    while(currNode != NULL){        //traverse list until key word matched, then return it, if not found, return NULL
        if(strcmp(currNode->word, key) == 0){
            return currNode;
        }
        else{
            currNode = currNode->next;
        }
    }
    
    
    return NULL;
}

//find location in alphabetized list of word in given node

DListNode* FindABCLoc(DList* list, char* key){
	int i = 0;  //iteration
	int directionFlag = 0;  //differing behavior whether going from head to tail (1) of tail to head(-1)

	DListNode* currNode = NULL;

	if (list->head == NULL){    //empty list, return NULL
		return NULL;
	}
    
	if (key[0] < 'm'){  //determine whether to start search at head or tail
		currNode = list->head;
		directionFlag = 1;
		i = 0;
	}
	else{
		currNode = list->tail;
		directionFlag = -1;
		i = list->size - 1;

	}

	while (i >= 0 && i < list->size){   //while within bound of list size, find place in list
			
        if (strcmp(key, currNode->word) == 0) { //if found match, return NULL, Create and Count function that called this funct will take care of the rest
            return currNode;
        }
        
		switch (directionFlag){
		case 1:
			if (currNode->next == NULL){    //if at tail return current to insert after
				return currNode;
			}
            if (strcmp(key, currNode->word) < 0){    //if you've gone past what should have been a match if it existed, return previous

                return currNode->prev;
                
                    
            }
			currNode = currNode->next; //traverse list
			i++;
			break;

		case -1:
			if (currNode->prev == NULL){    //if at head return NULL to insert at head
				return NULL;
			}
            if (strcmp(key, currNode->word) > 0){   //if you've gone past what should have been a match if it existed, return current
                return currNode;
            }
			currNode = currNode->prev;  //traverse list
			i--;
			break;
		}
    }
	
	return NULL;
}

//remove node from given list

bool DListRemove(DList* list, DListNode* currNode){

	if (currNode->prev != NULL){    //if not at the beginning of list, reroute links for next item
		currNode->prev->next = currNode->next;
		list->tail = currNode->prev;
	}
	if (currNode->next != NULL){    //if not at end of list, reroute links for prev item
		currNode->next->prev = currNode->prev;
		list->head = currNode->next;
	}
	if(currNode->prev == NULL && currNode->next == NULL){   //if only item in list, set list values to reflect removal
		list->head = NULL;
		list->tail = NULL;
	}
	
	free(currNode->word);
	free(currNode);
	list->size--;

	return true;
}

//print entire list to screen

void DListPrint(DList* list){

	DListNode* currNode = list->head;

	while (currNode != NULL){   //traverse list, print each word and frequency to screen
		if (strcmp(currNode->word, " ") != 0){
			printf("%s  (%+ld)\n", currNode->word, currNode->endCount - currNode->startCount);
		}
		else{
			printf("--less than five trending--\n");
		}
		currNode = currNode->next;
	}
	printf("\n");
//    printf("(%d)\n\n", list->size);
	return;
}

//print entire list to file

void DListFprint(FILE* output, DList* list){
    
    DListNode* currNode = list->head;
   
	while (currNode != NULL){       //traverse list, print each word and frequency to file
		if (strcmp(currNode->word, " ") != 0){
			fprintf(output, "%s  (%+ld)\n", currNode->word, currNode->endCount - currNode->startCount);
		}
		else{
			fprintf(output, "--less than five trending--\n");
		}
		currNode = currNode->next;
	}
	fprintf(output, "\n");
    fprintf(output, "(%d)\n\n", list->size);
    return;
}

//initialize values for node, allocates memory for char* word

void DListNodeInit(DListNode* node){
    
    node->word = (char*)malloc((strlen(" ") + 1) * sizeof(char));   //allocate memory, check that it has been allocated
	if (node->word == NULL){
		printf("Error, malloc failed to reserve data.");
		exit(EXIT_FAILURE);
	}
    strcpy(node->word, " ");//intialize to empty space, 0 or NULL
    node->startCount = 0;
    node->endCount = 0;
    node->next = NULL;
    node->prev = NULL;
}
