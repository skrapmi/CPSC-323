/******************************************************************
 * Members: Tim, Luis, Stephen                                    *
 * Class:   CS-323 Compilers                                      *
 * Project: Assignment 2 - JSON Parser                            *
 * File:    main.cpp                                              *
 * Date:    July 19,2017                                          *
 *****************************************************************/


#include <iostream>
#include <fstream>
#include "ast.h"
#include <regex>

using namespace std;


int main(int argc, char *argv[0]) {
  	// Declare a string variable to store a filename
  	std::string aFile;
	string		buf;	
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

	regex	objectRE("");
	regex 	arrayRE("");
	regex   jLineRE(R"("(("\w+")\s*:\s* (\w+),)");
	regex   jIntRE(R"("\d+")");

    cmatch	fileTypeMatch;
    cmatch  jLineMatch;
    cmatch  jValMatch;
    cmatch  jIntMatch;

    string  jsonID;
    string   jsonVal;

	bool	isObjectOrArray;
	bool    isValidLine;

/*
	if(isObjectOrObject = true) //reg_search(buf, fileTypeMatch, objectRE)
		{
		JsonObject* 	jObject = new JsonObject();
		} 
	else if (isObjectOrObjec = false){
		}
*/

    do {
        getline(inFile, buf);
        
        if(regex_search(buf, jLineMatch, jLineRE))
            {
            jsonID = jLineMatch.str(1);
            jsonVal = jLineMatch.str(2);

            cout << "ID: " << jsonID << endl;
            cout << "VAL: " << jsonVal << endl;
            }

        else {
            cout << "Not a valid line! \n";
            }
        
        if (regex_search(jsonVal, jIntMatch, jIntRE)) {
            int i = stoi(jsonVal);

            cout << "Valid Int " << i << " matched! \n";
            //jObject->Add(jsonID, new JsonNmber(i));
            }

                 
                
        } while (!inFile.eof());
		
	
	return 0;
}
