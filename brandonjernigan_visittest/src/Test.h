/*
Name: Brandon Jernigan
NetID: brandonjernigan
Date: 11/15/2014
File: Test.h

Description:	This is the .h file for a set of funcitons for testing Visit class functions for expected output given varying sets of input.
*/
#ifndef TEST_H
#define TEST_H

#include "Visit.h"

using namespace std;

bool testConstructor();			//Tests whether Visits constructor works as expected

bool testCompare();				//Tests whether Visits compare function works as expected

bool testAddState();			//Tests whether Visits addState function works as expected

bool testGetVisitString();		//Calls testString to examine several cases in the getVisits funciton 

bool testString(string inputString, double start, double end);	//Tests whether Visits getVisitString function works as expected given particular arguments given in testGetVisitString

#endif