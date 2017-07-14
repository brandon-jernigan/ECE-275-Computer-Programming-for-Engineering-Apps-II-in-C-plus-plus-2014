/*
Name: Brandon Jernigan
NetID: brandonjernigan
Date: 11/15/2014
File: Test.cpp

Description:	This is the .cpp file for a set of funcitons for testing Visit class functions for expected output given varying sets of input.
*/

#include "Test.h"
#include "Visit.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;



bool testConstructor(){			//Tests whether Visits constructor works as expected.
	bool result = true;	//default to true since cases exaimined in the function are those that fail and should flag the return value as false.
	Visit testVisit1("Location1", 1, 2);	//Three arguments are given to the testVisit1 constructor.


	// All three arguments given to testVisit1 are examined to ensure they match the values, there should also be no states in the states vector.
	if (testVisit1.getLocation() != "Location1" || testVisit1.getStartTime() != 1 || testVisit1.getEndTime() != 2 || testVisit1.getStates().size() != 0){
		result = true;
	}

	return result;
}

bool testCompare(){				//Tests whether Visits compare function works as expected.
	bool result = true;	//default to true since cases exaimined in the function are those that fail and should flag the return value as false.
	Visit testVisit1("", 0, 0);	
	Visit testVisit2("", 0, 0);	//These two Visit objects will be compared to one another in the compare funciton. Currently set to arbitrary values.


	testVisit1.setLocation("Location1");
	testVisit1.setStartTime(1);
	testVisit1.setEndTime(2);

	testVisit2.setLocation("Location1");
	testVisit2.setStartTime(3);
	testVisit2.setEndTime(4);

	if (!Visit::compare(&testVisit1, &testVisit2)){	//This first test gives is expected to have compare return true for the same location in chronological order,
													//which means that they will not need to be swapped by the sort funciton elsewhere in the gpsimu project
		result = false;
	}

	testVisit1.setLocation("location1");
	testVisit1.setStartTime(1);
	testVisit1.setEndTime(2);

	testVisit2.setLocation("Location1");
	testVisit2.setStartTime(3);
	testVisit2.setEndTime(4);

	if (!Visit::compare(&testVisit1, &testVisit2)){	//This test is the same as the previous, but will catch if the compare function is case-sensitive,
													//it should not be. Compare will return true.
		result = false;
	}

	testVisit1.setLocation("Location1");
	testVisit1.setStartTime(3);
	testVisit1.setEndTime(4);

	testVisit2.setLocation("Location1");
	testVisit2.setStartTime(1);
	testVisit2.setEndTime(2);

	if (Visit::compare(&testVisit1, &testVisit2)){	//This test gives the same location, but out of chronogical order. Compare should return false
													//so that they can be swapped and put into chronological order
		result = false;
	}



	testVisit1.setLocation("Location1");
	testVisit1.setStartTime(1);
	testVisit1.setEndTime(2);

	testVisit2.setLocation("Location2");
	testVisit2.setStartTime(3);
	testVisit2.setEndTime(4);

	if (!Visit::compare(&testVisit1, &testVisit2)){	//This test gives two locations in alphabetical order and chronological order.
													//Compare should return true.
		result = false;
	}



	testVisit1.setLocation("Location1");
	testVisit1.setStartTime(3);
	testVisit1.setEndTime(4);

	testVisit2.setLocation("Location2");
	testVisit2.setStartTime(1);
	testVisit2.setEndTime(2);

	if (!Visit::compare(&testVisit1, &testVisit2)){	//This test gives two locations in alphabetical order, but out of chronological order.
													//These will not need to be swapped by a sort funciton because chronological order is secondary
													//to alphabetical. Compare should return true.
		result = false;
	}



	testVisit1.setLocation("Location2");
	testVisit1.setStartTime(1);
	testVisit1.setEndTime(2);

	testVisit2.setLocation("Location1");
	testVisit2.setStartTime(3);
	testVisit2.setEndTime(4);

	if (Visit::compare(&testVisit1, &testVisit2)){	//This test gives two locations out of alphabetical order, but in chronological order.
													//These will need to be swapped since alphabetical order is primary to chronological order.
													//Compare should reurn false.
		result = false;
	}



	testVisit1.setLocation("Location2");
	testVisit1.setStartTime(3);
	testVisit1.setEndTime(4);

	testVisit2.setLocation("Location1");
	testVisit2.setStartTime(1);
	testVisit2.setEndTime(2);

	if (Visit::compare(&testVisit1, &testVisit2)){	//This test gives two locations out of both alphabetical and chronological order.
													//These will need to be swapped since they are out of alphabetical order.
													//Compare should return false.
		result = false;
	}


	return result;
}

bool testAddState(){				//Tests whether Visits addState function works as expected.
	bool result = true;	//default to true since cases exaimined in the function are those that fail and should flag the return value as false.
	Visit testVisit("Location1", 1, 2);	//Visit object used to test correct operation of addState funciton.
	

	testVisit.addState("State1");	

	//adding a single state, states vector should only have a size of 1.
	if (testVisit.getStates().at(0) != "State1" || testVisit.getStates().size() != 1){
		result = false;
	}

	
	testVisit.addState("State2");
	
	//After adding a second state. All vector locations are examined. States vector should only have a size of 2.
	if (testVisit.getStates().at(0) != "State1" || testVisit.getStates().at(1) != "State2" || testVisit.getStates().size() != 2){
		result = false;
	}


	testVisit.addState("State2");

	//After adding a repeat of the last state. Function should not add to the states vector.
	//All vector locations are examined. States vector should still only have a size of 2.
	if (testVisit.getStates().at(0) != "State1" || testVisit.getStates().at(1) != "State2" || testVisit.getStates().size() != 2){
		result = false;
	}


	return result;
}

bool testGetVisitString(){			//Calls testString to examine several cases in the getVisits funciton .
	bool result = true;	//default to true since cases exaimined in the function are those that fail and should flag the return value as false.


	//test all combinations of valid and invalid(empty) locations, negative and positive start/end times, and ordered/disordered/identical start/end times.
	//All of these should return true.
	if(testString("Location1", 1, 2) && testString("Location1", -1, 2) && testString("Location1", -1, -2)
		&& testString("Location1", 1, -2) && testString("Location", 2, 1) && testString("Location", 1, 1) && testString("", 1, 2) && testString("", -1, 2)
		&& testString("", -1, -2) && testString("", 1, -2) && testString("", 2, 1) && testString("", 1, 1)){
	}
	else {
		result = false;
	}



	return result;
}

bool testString(string inputString, double start, double end){	//Tests whether Visits getVisitString function works as expected given particular arguments given in testGetVisitString.
	bool result = true;	//default to true since cases exaimined in the function are those that fail and should flag the return value as false.
	
	string location;	//All following string variables hold one word in the string output by getVisitsString
	string startTime;
	string realStart;
	string to;
	string endTime;
	string realEnd;
	string states;
	string state1;
	string state2;
	string state3;
	string trash;

	Visit testVisit(inputString, start, end);	//Visit object to be tested.

	ostringstream oSS1;	//output string stream for holding double startTime as string
	ostringstream oSS2;	//output string stream for holding double endTime as string in following section.
	
	oSS1 << setprecision(8) <<  showpoint << start;

	realStart = oSS1.str();

	oSS2 << setprecision(8) << showpoint << end;

	realEnd = oSS2.str();


	istringstream inSS1(testVisit.getVisitString());	//input string stream holds output of getVisitsString funciton for further testing.

	inSS1 >> location;


	if ((inputString != "" && location != inputString) || (inputString == "" && location != "ERROR!")){	//if location input was empty and not equal to actual input
																										//or if location was empty and ERROR! was not produced.
		result = false;
	}


	
	if (start > end && start >= 0 && end >= 0){	//first check whether start and end times are both positive and in correct order and throw correct ERROR! codes

		inSS1 >> startTime;
		if (startTime != "ERROR!"){
			result = false;
		}
		inSS1 >> to;
		if (to != "to"){
			result = false;
		}
		inSS1 >> endTime;
		if (endTime != "ERROR!"){
			result = false;
		}
	}
	else {	//otherwise check whether any of the times are negative and throw correct ERROR! codes

		inSS1 >> startTime;

		if (start >= 0 && startTime != realStart){	//start must be positive or show an ERROR!
			result = false;
		}

		if (start < 0 && startTime != "ERROR!"){
			result = false;
		}


		inSS1 >> to;

		if (to != "to"){	//check format
			result = false;
		}


		inSS1 >> endTime;

		if (end >= 0 && endTime != realEnd){	//end must be positive or show an ERROR!
			result = false;
		}

		if (end < 0 && endTime != "ERROR!"){
			result = false;
		}
	}

	inSS1 >> states;
	if(states != "States:"){	//check format
		result = false;
	}

	inSS1 >> state1;

	if(state1 != "ERROR!"){	//empty states vector should show ERROR!
		result = false;
	}

	inSS1.clear();

	testVisit.addState("State1");	//initialize states vector
	testVisit.addState("State2");
	testVisit.addState("State3");

	istringstream inSS2(testVisit.getVisitString());	//refresh getVisits string with new States

	inSS2 >> trash >> trash >> trash >> trash;
	inSS2 >> states;

	if(states != "States:"){
		result = false;
	}

	inSS2 >> state1;
	inSS2 >> state2;
	inSS2 >> state3;

	if (state1 != "State1," || state2 != "State2," || state3 != "State3"){	//Makes sure all three states show up correctly
		result = false;
	}

	inSS2.clear();

	return result;
}