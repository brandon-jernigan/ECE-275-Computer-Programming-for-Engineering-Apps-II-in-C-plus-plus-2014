/*
Name: Brandon Jernigan
NetID: brandonjernigan
Date: 11/15/2014
File: main.cpp

Description: This is the main.cpp file for a program that tests the Visit.cpp file from the previous program, gpsimu. 
			 Several test cases are input into the functions of the Visit class and their output is exaimined for
			 the correct values and format.
*/

#include "Test.h"
#include <iostream>

int main( int argc, char *argv[])	//Main funciton, no command line arguments will be utilized.
{
	cout << "Beginning tests." << endl;	//Indicates beginning of test sequence.


	if (testConstructor()){		//Test whether Visits constructor works as expected
		cout << "   UNIT TEST PASSED: Visit()" << endl;
	}
	else{
		cout << "   UNIT TEST FAILED: Visit()" << endl;
	}


	if (testCompare()){		//Test whether Visits compare function works as expected
		cout << "   UNIT TEST PASSED: compare()" << endl;
	}
	else{
		cout << "   UNIT TEST FAILED: compare()" << endl;
	}

	
	if (testAddState()){	//Test whether Visits addState function works as expected
		cout << "   UNIT TEST PASSED: addState()" << endl;
	}
	else{
		cout << "   UNIT TEST FAILED: addState()" << endl;
	}


	if (testGetVisitString()){	//Test whether Visits getVisistString function works as expected
		cout << "   UNIT TEST PASSED: getVisitString()" << endl;
	}
	else{
		cout << "   UNIT TEST FAILED: getVisitString()" << endl;
	}


	cout << "Tests complete." << endl;	//Indicates end of testing sequence.
	return 0;
}