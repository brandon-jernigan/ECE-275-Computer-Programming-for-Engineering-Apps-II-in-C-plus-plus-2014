// File: trending.c
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description: This is the .c file for finding which members of an alphabetized list of words and start/end frequencies have increased and decreased the greatest,
// the top five for each criteria are then stored in 2 seperate lists.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trending.h"
#include "dlist.h"
#include "bool.h"

//finds top 5 trending up and top 5 trending down given an alphabetized list

void trending(DList* list){
    
    int i = 0;  //iterate var
    long difference1 = 0;   //difference for current node on alphabetized list
    long difference2 = 0;   //difference for tail of upList
	long difference3 = 0;   //difference for tail of downList
	long difference4 = 0;   //difference for searching upList
	long difference5 = 0;   //difference for searching downList
    DListNode* currNode = NULL; //stores node for traversing alphabetized list
    DListNode* trendNode = NULL;    //stores node for traversing trend lists
    DListNode* newNode = NULL;  //stores node for memory allocation and addition to list
    DList* upList = NULL;   //stores top 5 trending up words and values
    DList* downList = NULL; //stores top 5 trending down words and values
    
    upList = (DList*)malloc(sizeof(DList)); //allocate memory for uplist, check that it has been allocated
	if (upList == NULL){
		printf("Error, malloc failed to reserve data.");
		exit(EXIT_FAILURE);
	}
    DListInit(upList);  //initialize list values

    downList = (DList*)malloc(sizeof(DList));   //allocate memory for downList, check that it has been allocated
	if (downList == NULL){
		printf("Error, malloc failed to reserve data.");
		exit(EXIT_FAILURE);
	}
    DListInit(downList);    //initialize list values
    
    for(i = 0; i < 5; i++){ //create 5 member list for upList
        newNode = (DListNode*)malloc(sizeof(DListNode));    //allocate memory, check that it has been allocated
		if (newNode == NULL){
			printf("Error, malloc failed to reserve data.");
			exit(EXIT_FAILURE);
		}
        DListNodeInit(newNode);//initialize node values
        DListInsertAfter(upList, NULL, newNode);
    }
    
    for(i = 0; i < 5; i++){ //create 5 member list for downList
        newNode = (DListNode*)malloc(sizeof(DListNode));    //allocate memory, check that it has been allocated
		if (newNode == NULL){
			printf("Error, malloc failed to reserve data.");
			exit(EXIT_FAILURE);
		}
        DListNodeInit(newNode); //initialize node values
        DListInsertAfter(downList, NULL, newNode);
    }
    
    
    currNode = list->head;
    
    while (currNode != NULL){   //go through entire list, calculating difference at each node and compare to difference of tail of each list
                                //if the difference is of greater magnitude for the appropriate list (+ for upList, - for downList)
                                //it is then compared to the other values on the list to select its position, the final item in each trend list
                                //is then removed, maintaining 5 nodes in each list
        
        difference1 = currNode->endCount - currNode->startCount;    //difference for current node on alphabetized list

		difference2 = upList->tail->endCount - upList->tail->startCount;    //difference for tail of upList

		difference4 = downList->tail->endCount - downList->tail->startCount;    //difference for searching upList

        if(difference1 > difference2){  //belongs on list if has greater trend (aka difference)
            
            trendNode = upList->head;   //start at head
            
            while(trendNode != NULL){   //until end of list

				difference3 = trendNode->endCount - trendNode->startCount;  //difference for tail of downList

                if(difference1 > difference3){  //belongs in list location if has greater trend (aka difference)
                    
					newNode = (DListNode*)malloc(sizeof(DListNode));    //allocate memory, check that it has been allocated
					if (newNode == NULL){
						printf("Error, malloc failed to reserve data.");
						exit(EXIT_FAILURE);
					}
					DListNodeInit(newNode); //initialize node

                    newNode->word = (char*)realloc(newNode->word, (strlen(currNode->word) + 1) * sizeof(char)); //reallocate memory, check that it has been allocated
					if (newNode->word == NULL){
						printf("Error, realloc failed to reserve data.");
						exit(EXIT_FAILURE);
					}
                    strcpy(newNode->word, currNode->word);  //copy values from alphabetized list node to node to be added to trend list
                    newNode->startCount = currNode->startCount;
                    newNode->endCount = currNode->endCount;
                    
                    DListInsertBefore(upList, trendNode, newNode);  //insert at given location
					DListRemove(upList, upList->tail);  //remove the tail item, as it no longer belongs on this list
					break;
				}
				else{
					trendNode = trendNode->next;    //traverse trend list
				}
                
            }
		}
		else if (difference1 < difference4){    //belongs on list if has lesser trend (aka difference)
            
            trendNode = downList->head; //start at head
            
            while(trendNode != NULL){   //until end of list

				difference5 = trendNode->endCount - trendNode->startCount;  //difference for searching downList

                if(difference1 < difference5){  //belongs in list location if has lesser trend (aka difference)
                    
					newNode = (DListNode*)malloc(sizeof(DListNode));    //allocate memory, check that it has been allocated
					if (newNode == NULL){
						printf("Error, malloc failed to reserve data.");
						exit(EXIT_FAILURE);
					}
					DListNodeInit(newNode);  //initialize node
                    
                    newNode->word = (char*)realloc(newNode->word, (strlen(currNode->word) + 1) * sizeof(char)); //reallocate memory, check that it has been allocated
					if (newNode->word == NULL){
						printf("Error, realloc failed to reserve data.");
						exit(EXIT_FAILURE);
					}
                    strcpy(newNode->word, currNode->word);  //copy values from alphabetized list node to node to be added to trend list
                    newNode->startCount = currNode->startCount;
                    newNode->endCount = currNode->endCount;
                    
                    DListInsertBefore(downList, trendNode, newNode);    //insert at given location
					DListRemove(downList, downList->tail);  //remove the tail item, as it no longer belongs on this list
					break;
				}
				else{
					trendNode = trendNode->next;    //traverse trend list
				}
                
            }
        }

    
        
        currNode = currNode->next;  //traverse alphabetized list
    }
    
	printf("\nTrending Up:\n"); //print results to screen and destroty trending lists
    DListPrint(upList);
	DListDestroy(upList);

	printf("Trending Down:\n");
    DListPrint(downList);
	DListDestroy(downList);

	return;
}

