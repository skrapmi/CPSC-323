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
	regex storageStartType(R"(\s*(\{|\[))");
	regex storageEndType(R"(\s*(\}|\]))");
	regex str(R"(\s+\x22(\w+)\x22:\s+\x22(\w+)\x22)");
	regex num(R"(\s+\x22(\w+)\x22:\s+(\d+))");		
	regex bol(R"(\s+\x22(\w+)\x22:\s+(\w+))");
	regex arr(R"(\s+\x22(\w+)\x22:\s+\[\s*(.+)\s*\])");
	smatch storMatch;
	smatch strMatch;
  smatch numMatch;
	smatch bolMatch;
	smatch arrMatch;


	JsonObject* o = new JsonObject();

	try{
		getline(file, buf);
		storFound = regex_search(buf, storMatch, storageStartType);

		if(storMatch.str(1) == "["){
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
		try {
			strFound = regex_search(buf, strMatch, str);
			numFound = regex_search(buf, numMatch, num); 
      bolFound = regex_search(buf, bolMatch, bol);
			arrFound = regex_search(buf, arrMatch, arr);
			storFound = regex_search(buf, storMatch, storageEndType);

	    if (strFound) {
				cout << "found String on line " << lineNum << endl;		
				cout << strMatch.str(2) << endl;
				if(isArrayType){
					o->Add(strMatch.str(1), new JsonString(strMatch.str(2)));
				}
		  } 

			else if(numFound) {
				cout << "found number on line " << lineNum << endl;
				cout << numMatch.str(2) << endl;
				if(!isArrayType){
					o->Add(strMatch.str(1), new JsonNumber(stoi(strMatch.str(2))));
				}
			}
			else if(bolFound && bolMatch.str(2) != "null"){
				cout << "found bool on line " << lineNum << endl;
				cout << bolMatch.str(2) << endl;
				
				if(!isArrayType){
					o->Add(strMatch.str(1), new JsonBoolean(strMatch.str(2) == "true"? true: false));
				}
			}
			else if(arrFound){
				cout << "found Array on line " << lineNum << endl;
				cout << arrMatch.str(0) << endl;
				if(!isArrayType){
					//call array function(
				}
			}
			else if(storFound && storMatch.str(0) == "}"){
				cout << "found end of Array or Object " << lineNum << endl;
				exit(0);
			}
			else
				cout << "Parse file error on line " << lineNum << endl;
		} 
	  catch (regex_error& e) {
			// Syntax error in the RE
	    cout << "JSON File Error on line " << lineNum << endl;
		}

		if(isArrayType){
			//call array function(
		}	
	} while(!file.eof()); 
}
