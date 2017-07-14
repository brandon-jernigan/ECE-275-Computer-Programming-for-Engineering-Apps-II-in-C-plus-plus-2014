// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: Pathsearch.cpp
//
// Description:

#include "Graph.h"
#include "Street.h"
#include "Waypoint.h"
#include "PathSearch.h"
#include <vector>
#include <algorithm>
#include <queue>

void PathSearch::reliableSearch(int start, int end, Graph* graph){
	unsigned int i = 0;
	double distance = LARGE_NUMBER;
	double min = 0;
	double max = 0;
	double maxDist = graph->findWaypoint(graph, end)->getMaxDistance();
	vector<string> path;
	int noPathFlag = 0;
	Waypoint* curWP = graph->findWaypoint(graph, start);

	for(i = 0; i > graph->getWaypoints().size(); i++){
		graph->getWaypoints().at(i)->setPredecessor(NULL);

	}

	graph->setUnvisited(graph->getWaypoints());

	curWP->setDistance(0);
	curWP->setDifference(0);

	curWP = queueFront(graph);


	// compare each connected waypoints current distance with new distance from start
	// if new distance is smaller, replace that waypoint's distance with new distance
	// remove waypoint from priority queue once all connected waypoints have been evaluated
	// repeat until priority queue empty
	while (!graph->getUnvisited().empty()){

		for (i = 0; i < curWP->getStreets().size(); i++){
			

			if(curWP->getStreets().at(i)->getEndWP()->getDistance() <= maxDist){

				if (curWP->getStreets().at(i)->getEndWP()->getDifference()
					> (curWP->getDifference() + abs(curWP->getStreets().at(i)->getMinTravelTime() - curWP->getStreets().at(i)->getMinTravelTime()))){

			
					curWP->getStreets().at(i)->getEndWP()->setPredecessor(curWP->getStreets().at(i));

					curWP->getStreets().at(i)->getEndWP()->
						setDifference(curWP->getDifference() + abs(curWP->getStreets().at(i)->getMinTravelTime() - curWP->getStreets().at(i)->getMinTravelTime()));
				}
			}
		}
		curWP = queueFront(graph);
	}

	curWP = graph->findWaypoint(graph, end);
	end = curWP->getId();

	if(curWP->getPredecessor() != NULL){

		for (i = 0; curWP->getPredecessor() != NULL; i++){

			min += curWP->getPredecessor()->getMinTravelTime();
			max += curWP->getPredecessor()->getMaxTravelTime();

			path.push_back(curWP->getName());

			curWP = curWP->getPredecessor()->getStartWP();
		}
	} else if(start != end){
		noPathFlag = 1;
	}

	path.push_back(curWP->getName());
	start = curWP->getId();

	if(noPathFlag ==1){
		cout << "No routes found." << endl;
	} 
	else{

		cout << "Most reliable path: " << start << " to " << end << " (" << min << " to " << max << ")" << endl;

		for (i = 0; i < path.size(); i++){
			cout << " " << path.at(path.size() - 1 - i) << endl;
		}
		cout << endl;
	}
	return;
}

void PathSearch::shortestSearch(int start, int end, Graph* graph){
	unsigned int i = 0;
	double distance = LARGE_NUMBER;
	double min = 0;
	double max = 0;
	vector<string> path;
	int noPathFlag = 0;
	Waypoint* curWP = graph->findWaypoint(graph, start);

	graph->setUnvisited(graph->getWaypoints());

	curWP->setDistance(0);
	curWP->setPredecessor(NULL);


	curWP = queueFront(graph);


	// compare each connected waypoints current distance with new distance from start
	// if new distance is smaller, replace that waypoint's distance with new distance
	// remove waypoint from priority queue once all connected waypoints have been evaluated
	// repeat until priority queue empty
	while (!graph->getUnvisited().empty()){

		for (i = 0; i < curWP->getStreets().size(); i++){
			if (curWP->getStreets().at(i)->getEndWP()->getDistance()
				> (curWP->getDistance() + curWP->getStreets().at(i)->getMinTravelTime())){

				curWP->getStreets().at(i)->getEndWP()->setPredecessor(curWP->getStreets().at(i));

				curWP->getStreets().at(i)->getEndWP()->
					setDistance(curWP->getDistance() + curWP->getStreets().at(i)->getMinTravelTime());

				curWP->getStreets().at(i)->getEndWP()->
					setMaxDistance(curWP->getMaxDistance() + curWP->getStreets().at(i)->getMaxTravelTime());
			}
		}
		curWP = queueFront(graph);
	}

	curWP = graph->findWaypoint(graph, end);
	end = curWP->getId();
	if(curWP->getPredecessor() != NULL){

		for (i = 0; curWP->getPredecessor() != NULL; i++){

			min += curWP->getPredecessor()->getMinTravelTime();
			max += curWP->getPredecessor()->getMaxTravelTime();

			path.push_back(curWP->getName());

			curWP = curWP->getPredecessor()->getStartWP();
		}
	} else if(start != end){
		noPathFlag = 1;
	}

	path.push_back(curWP->getName());
	start = curWP->getId();

	if(noPathFlag ==1){
		cout << "No routes found." << endl;
	} 
	else{

		cout << "Shortest path: " << start << " to " << end << " (" << min << " to " << max << ")" << endl;

		for (i = 0; i < path.size(); i++){
			cout << " " << path.at(path.size() - 1 - i) << endl;
		}
		cout << endl;
	}
	return;
}

Waypoint* PathSearch::queueFront(Graph* graph){
	unsigned int i = 0;
	vector<Waypoint*> unvisited = graph->getUnvisited();
	Waypoint* result = NULL;

	sort(unvisited.begin(), unvisited.end(), sortByDistance1);

	if(unvisited.size() > 0){
		result = unvisited.at(unvisited.size() - 1);
		unvisited.pop_back();
		graph->setUnvisited(unvisited);
	}

		return result;

}