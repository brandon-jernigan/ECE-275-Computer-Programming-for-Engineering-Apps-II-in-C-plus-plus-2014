Author: Brandon Jernigan
NetID: brandonjernigan
Date: 9/15/2014
Assignment: 1

This program receives an input and output file location for AC temperature data consisting of the time in the format HH:MM and the temperature in the format TT.T, then reads the file. The data is then read for any invalid readings, which are 5 or more above, and 5 or more below the previous temperature. Then a low pass filter is applied. The valid, filtered data is then processed to determine the state of the AC at any particular time. After this the data is written to a file, and the program exits.