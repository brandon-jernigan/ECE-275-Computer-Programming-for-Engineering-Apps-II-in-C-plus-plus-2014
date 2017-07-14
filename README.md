# ECE-275-Computer-Programming-for-Engineering-Apps-II-in-C-plus-plus-2014

C and C++ programming. Core design and analysis of engineering algorithms and structures including lists, trees, graphs, traversal, and encoding. Fundamentals of C and C++ programming languages including pointers, structures, unions, and introduction to classes. Programming design topics including memory management, abstraction and design of advanced structures, and basics of software engineering.

Assignments:

1-tempfilter
This program receives an input and output file location for AC temperature data consisting of the time in the format HH:MM and the temperature in the format TT.T, then reads the file. The data is then read for any invalid readings, which are 5 or more above, and 5 or more below the previous temperature. Then a low pass filter is applied. The valid, filtered data is then processed to determine the state of the AC at any particular time. After this the data is written to a file, and the program exits.

2-trending
This program takes two input files containing a list of words and finds which 5 words increase in frequency the most and which 5 words decrease in frequency the most. This will be carried out by alphabetizing the wordsin a doubly linked list with frequency data, and by sorting through this list to find which words match the stated criteria.

3-gpsimu
This program takes input gpsimu data from an autonomous vehicle. It compares this data with a set of known locations and determines the journey of the vehicle along with the vehicle states during its journey.

4-visitest
This is a program that tests the Visit.cpp file from the previous program, gpsimu. Several test cases are input into the functions of the Visit class and their output is exaimined for the correct values and format.

5 -weighs
This program searches for the optimal route to travel to a location based on the shortest, and longest, potential travel times along a route. It uses dijkstra's shortest path algorithm on a weighted graph.
