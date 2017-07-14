// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: Street.h
//
// Description:

#ifndef STREET_H
#define STREET_H

class Waypoint;

class Street{

public:

	Street() : startId(0), endId(0), minTravelTime(0), maxTravelTime(0){
		return;
	}

	~Street(){ return; }

	Waypoint* adjWaypoint;

	void setStartId(int startId){ this->startId = startId; return; }

	int getStartId(){ return this->startId; }

	void setEndId(int endId){ this->endId = endId; return; }

	int getEndId(){ return this->endId; }

	void setMinTravelTime(double minTravelTime){ this->minTravelTime = minTravelTime; return; }

	double getMinTravelTime(){ return this->minTravelTime; }

	void setMaxTravelTime(double maxTravelTime){ this->maxTravelTime = maxTravelTime; return; }

	double getMaxTravelTime(){ return this->maxTravelTime; }

	void setStartWP(Waypoint* waypoint){ this->startWP = waypoint; return; }

	Waypoint* getStartWP(){ return this->startWP; }

	void setEndWP(Waypoint* waypoint){ this->endWP = waypoint; return; }

	Waypoint* getEndWP(){ return this->endWP; }

private:

	int startId;

	int endId;

	double minTravelTime;

	double maxTravelTime;

	Waypoint* startWP;

	Waypoint* endWP;
	
};

#endif