/******************************************************************
 * Members: Tim, Luis, Stephen                                    *
 * Class:   CS-323 Compilers                                      *
 * Project: Assignment 2 - JSON Parser                            *
 * File:    main.cpp                                              *
 * Date:    July 19,2017                                          *
 *****************************************************************/


#include <iostream>
#include <fstream>
#include <regex>
#include "ast.h"


using namespace std;

void parseADT(ifstream&);

int main(int argc, char *argv[0]) {
  // Declare a string variable to store a filename
  std::string aFile;

  // Declare a variable to read in a JSON file
  ifstream inFile;

  // Check for a command line argument
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <filename>\n";
  } else {
    // store the command argument as the filename
    aFile = argv[1];
  }

  // Read in a .json file
  inFile.open(aFile);

  // Check that the file name was opened successfully
  if (inFile.fail( )) {
    // Print an error message
    cout << "Error opening file.\n\n";
    exit(1);
  } else {
    // The file was successfully opened
    cout << "File opened successfully.\n\n";
  }

	parseADT(inFile);

return 0;
}


void parseADT(ifstream &file){
	int 		lineNum = 1;
	string  buf;
	bool 		isArrayType = false;
	bool    strFound 		= false;
  bool    numFound 		= false;    
  bool    bolFound 		= false;
	bool		arrFound 		= false;
	bool 		storFound 	= false;
	JsonObject o;// = new JsonObject();
	try{
		getline(file, buf);
		regex storageType(R"(\{|\[)");
		smatch storMatch;
		storFound = regex_search(buf, storMatch, storageType);

		if(storMatch.str(0) == "["){
			cout << "found true\n";			
			isArrayType = true;
		}
	}
	catch(regex_error& e){
		cout << "Invalid JSON storage file.  Please check file neither array or object found\n\n";
		exit(0);
	}
	do{
		lineNum++;
		getline(file, buf);
		if(isArrayType){
			try {
		    regex str(R"(\w+)");
				regex num(R"(\w+)");
				regex bol(R"(\w+)");
				regex arr(R"(\w+)");

		    smatch strMatch;
		    smatch numMatch;
				smatch bolMatch;
				smatch arrMatch;

				strFound = regex_search(buf, strMatch, str);
				numFound = regex_search(buf, numMatch, num); 
        bolFound = regex_search(buf, bolMatch, bol);
				arrFound = regex_search(buf, arrMatch, arr);

		    if (strFound) {
					//secStr = strMatch.str(1);
			  } 

				else if(numFound) {
		      //propStr = numMatch.str(1);
					//valStr = match.str(2);
				}
				else if(bolFound){

				}
				else if(arrFound){

				}
			} 
		  catch (regex_error& e) {
				// Syntax error in the RE
		    cout << "JSON File Error on line " << lineNum << endl;
			}
		}
		else {
			try {
		    regex str(R"(\s+\x22(\w+)\x22:\s+\x22(\w+)\x22)");
				regex num(R"(\s+\x22(\w+)\x22:\s+(\d+))");		
				regex bol(R"(\s+\x22(\w+)\x22:\s+(\w+))");
				regex arr(R"(\s+\x22(\w+)\x22:\s+(\[\w+\]))");
				
		    smatch strMatch;
		    smatch numMatch;
				smatch bolMatch;
				smatch arrMatch;

				strFound = regex_search(buf, strMatch, str);
				numFound = regex_search(buf, numMatch, num); 
        bolFound = regex_search(buf, bolMatch, bol);
				arrFound = regex_search(buf, arrMatch, arr);

		    if (strFound) {
					cout << "found String on line " << lineNum << endl;		
					cout << strMatch.str(2) << endl;
			  } 

				else if(numFound) {
					cout << "found number on line " << lineNum << endl;
					cout << numMatch.str(2) << endl;
		      //propStr = numMatch.str(1);
					//valStr = match.str(2);
				}
				else if(bolFound){
					cout << "found bool on line " << lineNum << endl;
					cout << bolMatch.str(2) << endl;
				}
				else if(arrFound){
					cout << "found Array on line " << lineNum << endl;
				}
				else
					cout << "Parse file error on line " << lineNum << endl;
			} 
		  catch (regex_error& e) {
				// Syntax error in the RE
		    cout << "JSON File Error on line " << lineNum << endl;
			}
    }
	
	} while(!file.eof()); 
}
