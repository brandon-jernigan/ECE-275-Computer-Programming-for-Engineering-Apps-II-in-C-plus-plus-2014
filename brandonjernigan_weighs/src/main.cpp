// Name: Brandon Jernigan
// NetID: brandonjernigan
// Date: 12/6/2014
// Assignment: 5
//
// File: main.cpp
//
// Description:

#include "Graph.h"
#include "PathSearch.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){
	Graph graph1;
	istringstream inSS;
	int start;;
	int end;

	if (argc != 4){
		cout << "Usage: weighs start end streetMapGraphFile" << endl;
		return -1;
	}

	graph1.parseFile(argv[3]);

	inSS.str(argv[1]);
	inSS >> start;
	inSS.clear();

	inSS.str(argv[2]);
	inSS >> end;
	inSS.clear();

	graph1.checkData(start, end);
	
	graph1.makeGraph();

	PathSearch::shortestSearch(start, end, &graph1);

	PathSearch::reliableSearch(start, end, &graph1);


	return 0;
}