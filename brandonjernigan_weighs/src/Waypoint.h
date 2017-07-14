// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: Waypoint.h
//
// Description:

#ifndef WAYPOINT_H
#define WAYPOINT_H

#define LARGE_NUMBER 1000000000000

#include <string>
#include <cmath>
#include <limits>

using namespace std;

class Street;

class Waypoint{

public:

	Waypoint() : id(0), name(""), distance(LARGE_NUMBER), difference(LARGE_NUMBER), maxDistance(0), minDistance(0), predecessor(NULL){
		return;

	}

	Waypoint(int id, string name, vector<Street*> streets, double distance){
		this->id = id;
		this->name = name;
		this->Streets = streets;
		this->distance = distance;
		return;
	}

	//bool operator()(Waypoint* lh, Waypoint* rh) const
	//{		
	//		
	//	if(lh->getDistance() == rh->getDistance()){
	//		return lh > rh;
	//	} else{
	//		return lh->getDistance() > rh->getDistance();
	//	}
	//}

	void addStreet(Street* street){ this->Streets.push_back(street); }

	~Waypoint(void){ return; }

	void setId(int id){ this->id = id; return; }

	int getId(){ return this->id; }

	void setName(string name){ this->name = name; return; }

	string getName(){ return this->name; }

	void setDistance(double distance){ this->distance = distance; return; }

	double getDistance(){ return this->distance; }

	void setDifference(double difference){ this->difference = difference; return; }

	double getDifference(){ return this->difference; }

	void setMaxDistance(double maxDistance){ this->maxDistance = maxDistance; return; }

	double getMaxDistance(){ return this->maxDistance; }

	void setMinDistance(double minDistance){ this->minDistance = minDistance; return; }

	double getMinDistance(){ return this->minDistance; }

	void setPredecessor(Street* predecessor){ this->predecessor = predecessor; return; }

	Street* getPredecessor(){ return this->predecessor; }

	vector<Street*> getStreets(){ return this->Streets; }

private:

	int id;

	string name;

	vector<Street*> Streets;

	double distance;

	double difference;

	double maxDistance;

	double minDistance;

	Street* predecessor;
};


#endif