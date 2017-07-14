// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: Graph.cpp
//
// Description:

#include "Graph.h"
#include "Waypoint.h"
#include "Street.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool Graph::checkData(int start, int end){
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int flag = 0;
		
	for (i = 0; i < this->Waypoints.size(); i++){
		if (this->Waypoints.at(i)->getId() == start){
			flag++;
		}
		if (this->Waypoints.at(i)->getId() == end){
			flag++;
		}
		for (j = i + 1; j < this->Waypoints.size(); j++){
			if (this->Waypoints.at(i)->getId() == this->Waypoints.at(j)->getId()){
				cout << "Duplicate waypoint, exiting program." << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	if (flag != 2){
		cout << "Start or end waypoint not found, exiting program." << endl;
		exit(EXIT_FAILURE);
	}
		
	flag = 0;

	for (i = 0; i < this->Streets.size(); i++){
		for (j = i + 1; j < this->Streets.size(); j++){
			if (this->Streets.at(i)->getStartId() == this->Streets.at(j)->getStartId()
					&& this->Streets.at(i)->getEndId() == this->Streets.at(j)->getEndId()){

				cout << "Duplicate street, exiting program." << endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	for (i = 0; i < this->Streets.size(); i++){
		for (j = 0; j < this->Waypoints.size(); j++){
			if (this->Streets.at(i)->getStartId() == this->Waypoints.at(j)->getId()){

				flag++;
			}
			if (this->Streets.at(i)->getEndId() == this->Waypoints.at(j)->getId()){

				flag++;
			}
		}
		if (flag < 2){
			cout << "Source or destination id not found, exiting program." << endl;
			exit(EXIT_FAILURE);
		}
		flag = 0;
	}
	return true;
}	

void Graph::makeGraph(){
	unsigned int i = 0;
	int id;

	for (i = 0; i < this->getStreets().size(); i++){
		id = this->getStreets().at(i)->getStartId();
		this->getStreets().at(i)->setStartWP(findWaypoint(this, id));
		findWaypoint(this, id)->addStreet(this->getStreets().at(i));

		id = this->getStreets().at(i)->getEndId();
		this->getStreets().at(i)->setEndWP(findWaypoint(this, id));
	}


	return;
}

bool Graph::parseFile(string fileName){
	unsigned int i = 0;
	int id = 0;
	int start = 0;
	int end = 0;
	double min = 0;
	double max = 0;
	fstream inFS;
	string line;
	string trash;
	istringstream inSS;

	inFS.open(fileName.c_str());


	if (!inFS.good()){
		cout << "Problem with file " << fileName << "." << endl;
		exit(EXIT_FAILURE);
	}

	getline(inFS, line);

	if(line != "WAYPOINTS:"){
		cout << "Incorrect organizaiton format." << endl;
		exit(EXIT_FAILURE);
	}

	getline(inFS, line);

	for (i = 0; line != ""; i++){
		inSS.clear();
		inSS.str(line);

		inSS >> id;

		if (id < 0){
			cout << "Incorrect ID format." << endl;
			exit(EXIT_FAILURE);
		}

		Waypoint* waypoint = new Waypoint();

		waypoint->setId(id);

		getline(inSS, line);

		if (line != "" && line != " "){
			while(line.at(0) == ' ' || line.at(0) == '\t'){ 
			line.erase(0, 1);
			}
		}
		else{
			cout << "Incorrect waypoint name format." << endl;
			exit(EXIT_FAILURE);
		}

		waypoint->setName(line);

		this->Waypoints.push_back(waypoint);

		getline(inFS, line);
	}

	getline(inFS, line);

	if (line != "STREETS:"){
		cout << "Incorrect organizaiton format." << endl;
		exit(EXIT_FAILURE);
	}

	getline(inFS, line);

	for (i = 0; inFS.good(); i++){

		inSS.clear();
		inSS.str(line);

		inSS >> start;
		inSS >> end;
		inSS >> min;
		inSS >> max;


		if (start < 0 || end < 0 || min < 0 || max < 0 || min > max){
			cout << "Incorrect street format." << endl;
			exit(EXIT_FAILURE);
		}
		
		Street* street = new Street();

		street->setStartId(start);

		street->setEndId(end);

		street->setMinTravelTime(min);

		street->setMaxTravelTime(max);

		this->Streets.push_back(street);

		getline(inFS, line);
	}

	//for (i = 0; i < this->Waypoints.size(); i++){
	//	cout << this->Waypoints.at(i)->getId() << " " << this->Waypoints.at(i)->getName() << endl;
	//}

	//for (i = 0; i < this->Streets.size(); i++){
	//	cout << this->Streets.at(i)->getStartId() << " " << this->Streets.at(i)->getEndId() << " " << this->Streets.at(i)->getMinTravelTime() << " " << this->Streets.at(i)->getMaxTravelTime() << endl;
	//}


	return true;
}

Waypoint* Graph::findWaypoint(Graph* graph, int id){
	Waypoint* result = NULL;
	unsigned int i = 0;

	for (i = 0; i < graph->getWaypoints().size(); i++){

		if (graph->getWaypoints().at(i)->getId() == id){

			result = graph->getWaypoints().at(i);
		}
	}

	return result;
}



Street* getStreets(int id){
	return NULL;
}