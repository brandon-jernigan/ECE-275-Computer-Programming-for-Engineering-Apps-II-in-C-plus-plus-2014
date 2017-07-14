// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: Pathsearch.h
//
// Description:
#ifndef PATHSEARCH_H
#define PATHSEARCH_H

#include "Waypoint.h"

namespace PathSearch{

	void reliableSearch(int start, int end, Graph* graph);

	void shortestSearch(int start, int end, Graph* graph);

	Waypoint* queueFront(Graph* graph);

	static bool sortByDistance1(Waypoint* lh, Waypoint* rh){
								
	if(lh->getDistance() == rh->getDistance()){
		if(lh->getMaxDistance() == rh->getMaxDistance()){
			return lh > rh;
		}
		else{
			return lh->getMaxDistance() > rh->getMaxDistance();
		}
	} 
	else{
		return lh->getDistance() > rh->getDistance();
	}
	}

	static bool sortByDistance2(Waypoint* lh, Waypoint* rh){
								
	if(lh->getDistance() == rh->getDistance()){
		if(lh->getMinDistance() == rh->getMinDistance()){
			if(lh->getMaxDistance() == rh->getMaxDistance()){
				return lh > rh;
			}
			else
			{
				return lh->getMaxDistance() > rh->getMaxDistance();
			}
		}
		else{
			return lh->getMinDistance() > rh->getMinDistance();
		}
	} 
	else{
		return lh->getDistance() > rh->getDistance();
	}
	}

}

#endif