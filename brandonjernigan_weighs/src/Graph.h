// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: Graph.h
//
// Description:

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <iostream>
#include "Waypoint.h"
#include "Street.h"

using namespace std;

class Graph {
	
public:

	Graph() : Waypoints(NULL), Streets(NULL) {
		return;
	}

	~Graph(){
		unsigned int i = 0;

		for (i = 0; i < this->Waypoints.size(); i++){
			delete this->Waypoints.at(i);
		}

		for (i = 0; i < this->Streets.size(); i++){
			delete this->Streets.at(i);
		}
		return;
	}

	void makeGraph();

	// Checks for duplicate waypoint id's, more than one street between two waypoints in same direction
	// Values passed for start and end not matching a waypoint id, street source or destination not matching waypoint id
	// exits program if errors found.
	bool checkData(int start, int end);

	bool parseFile(string graphFile);

	Waypoint* findWaypoint(Graph* graph, int id);

	bool makeGraph(Graph* graph);

	void setUnvisited(vector<Waypoint*> waypoints){
		this->Unvisited = waypoints; return;
	}


	void sortUnvisited(){
		unsigned int i = 0;
		for (i = 0; i < this->Unvisited.size(); i++){

		}
	}

	vector<Waypoint*> getUnvisited(){
		return this->Unvisited;
	}

	void setWaypoints(Waypoint* waypoint){
		this->Waypoints.push_back(waypoint); return;
	}

	vector<Waypoint*> getWaypoints(){
		return this->Waypoints;
	}

	void setStreets(Street* street){
		this->Streets.push_back(street); return;
	}

	vector<Street*> getStreets(){
		return this->Streets;
	}

//	Street* getStreets(int id);

private:

	vector<Waypoint*> Unvisited;

	vector<Waypoint*> Waypoints;

	vector<Street*> Streets;

};

#endif