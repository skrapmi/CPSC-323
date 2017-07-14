Timothy Parks
Luis Gonzalez
Stephen Cordasco

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
