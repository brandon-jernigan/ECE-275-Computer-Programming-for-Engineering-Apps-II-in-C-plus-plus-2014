/***
 Name: Jonathan Sprinkle
 Course: ECE275
 Assignment #: 3
 File: Visit.h
 */

#ifndef VISIT_H
#define VISIT_H


/***********************************************************************/
// included containers and strings
#include <string>
#include <vector>


/***********************************************************************/
/*
 Visit class
 
 This class is used to maintain an ordered list of the state of the
 GPSIMU while within range of a specific location.
 
 */
class Visit {
public:
	// Constructor and Destructor
	// Should be tested
	Visit( std::string location, double startTime, double endTime );
	// Need not be tested
	~Visit(void);
	
	// Should be tested
	// Compare two visits together to see which is before the other.
	// Returns true if v1 is before v2, false otherwise.
	// A visit is before another if its location is alphabetically before
	// the other visit’s location.
	// A visit with the same location name as another is before that
	// location if its startTime is before the other visit’s startTime.
	static bool compare(Visit* v1, Visit* v2);
	
	// Should be tested
    // Adds this state; if the stateString matches the last state in the
	// vector, then the operation returns without adding it to the vector
	void addState( std::string stateString );
	// Need not be tested
	// returns the states vector
	std::vector<std::string> getStates( ) const { return this->state; }
	
	// Should be tested
	// Returns the string for this visit. it looks as follows for a
	// location of "4th Avenue" between 100.00000 and 101.00001 with
	// states of [Init, Standby, Init]
	// (Note: no trailing spaces)
	//
	// 4th Avenue
	// 100.00000 to 101.00001
	// States: Init, Standby, Init
	//
	// If the States vector is empty, then it must print ERROR!
	// If the endTime is less than startTime, then instead of
	// printing the time it must print ERROR!
	// If the location is empty, it must print ERROR!
	std::string getVisitString( ) const;
	
	/* Mutators below do not need to be tested */
	void setStartTime( double startTime ) { this->startTime = startTime; }
	double getStartTime( ) const { return this->startTime; }
	
	void setEndTime( double endTime ) { this->endTime = endTime; }
	double getEndTime( ) const { return this->endTime; }
	
	void setLocation( std::string location ) { this->location = location; }
	std::string getLocation( ) const { return this->location; }
	
private:
	// Note that you can assume the week will always
	// be the same for start and end times.
	std::string location;      // The location name for this visit.
	double startTime;     // The start seconds for the visit.
	double endTime;       // The end seconds for the visit.
	std::vector<std::string> state; // The ordered list of states at this location.
};
#endif //VISIT_H