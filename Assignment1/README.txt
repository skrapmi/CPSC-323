Members: Timothy Parks
         Luis Gonzalez
         Stephen Cordasco

Class:   CS-323
Prof:    Kenytt Avery
Date:    July 14, 2017

Assignment 1: Scanning INI Files

Files: inifile.h inifile.cpp main.cpp

Description: This program reads in INI files and opens the file if
             it exists or prints an error message if the file was not
	     opened. Once the file is opened, the program scans the file
	     and extracts SECTIONS, PROPERTIES, and VALUES. The elements
	     are stored in maps; one map, 'map_data', has a key
	     represented as a string and a value represented as another
	     map. That map, 'data', has a key and value both represented
	     by a string. 'map_data' stores SECTIONS and its
	     corresponding PROPERTIES and VALUES which are stored as
	     keys and values, respectively. Each piece of data can be
	     accessed from the GetProfileString member function.

Compiling/Running: Use command: 'g++ -std=c++11 inifile.cpp main.cpp'
                   to build the program.
		   Then use command: './a.out filename'
		   where filename is the name of an INI file you want to
		   test.
		   Example: 'g++ -std=c++11 inifile.cpp main.cpp'
		            './a.out test.ini'
