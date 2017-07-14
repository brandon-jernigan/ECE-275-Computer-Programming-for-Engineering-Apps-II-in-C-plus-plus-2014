// File: trending.h
// Author: Brandon Jernigan
// Net Id: brandonjernigan
// Date: September 29, 2014

// Description: This is the .h file for finding which members of an alphabetized list of words and start/end frequencies have increased and decreased the greatest,
// the top five for each criteria are then stored in 2 seperate lists.

#include "bool.h"
#include "dlist.h"

#ifndef TRENDING_H
#define TRENDING_H

//finds top 5 trending up and top 5 trending down given an alphabetized list

void trending(DList* list);

#endif