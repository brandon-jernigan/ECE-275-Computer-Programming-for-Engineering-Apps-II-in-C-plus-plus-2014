/***
 Name: Jonathan Sprinkle
 Course: ECE275
 Assignment #: 3
 File: Visit.cpp
 */

/***********************************************************************/

#include "Visit.h"
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>

Visit::Visit(std::string location, double startTime, double endTime)
	: location(location), startTime(startTime), endTime(endTime), state()
{
	
}

Visit::~Visit( )
{
	// nothing to do
}

// Compare two visits together to see which is before the other.
// Returns true if v1 is before v2, false otherwise.
// A visit is before another if its location is alphabetically before
// the other visit’s location.
// A visit with the same location name as another is before that
// location if its startTime is before the other visit’s startTime.
bool Visit::compare(Visit *v1, Visit *v2)
{
	bool result=false;

	int strdiff = strcmpi(v1->getLocation().c_str(), v2->getLocation().c_str());

	if (strdiff < 0){
		result = true;
	}
	else if (strdiff == 0){
		if (v1->getStartTime() < v2->getStartTime()) {
			result = true;
		}
	}

	//if ( strdiff > 0) {
	//	result = true;
	//}
	//else if( strdiff == 0 )
	//{
	//	if (v1->getStartTime() < v2->getStartTime()) {
	//		result = true;
	//	}
	//}
	
	return result;
}

void Visit::addState(std::string stateString)
{
	if(this->getStates().size() != 0){

		if(this->getStates().back() != stateString){

			state.push_back(stateString);
		}
	}	
	else
	{
		state.push_back(stateString);
	}

	return;
}

std::string Visit::getVisitString() const
{
	std::stringstream result;
    std::string resultString;


	if(this->location != ""){
		result << this->location << std::endl;
	} 
	else{
		result << "ERROR!" << std::endl;
	}

	if (this->getStartTime() > getEndTime() && this->getStartTime() >= 0 && this->getEndTime() >= 0){
		result << "ERROR! to ERROR!" << std::endl;
	}
	else{
		if (this->getStartTime() >= 0){
			result << std::setprecision(8) << std::showpoint << this->getStartTime() << " to ";
		}
		else {
			result << "ERROR!" << " to ";
		}


		if (this->getEndTime() >= 0){
			result << std::setprecision(8) << std::showpoint << this->getEndTime() << std::endl;
		}
		else {
			result << "ERROR!" << std::endl;
		}
	}

	result << "States: ";
	if(this->state.size() != 0){
		for (std::vector<std::string>::const_iterator it=state.begin(); it!=state.end(); it++) {
			result << *it << ", ";
		}
	}
	else{
		result << "ERROR!--";
	}

	resultString = result.str();
    resultString = resultString.substr(0, resultString.length()-2);
	return resultString;
}