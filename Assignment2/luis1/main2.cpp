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

	regex	openBraceRE(R"(\s*[\{\[])");
    regex   closeBraceRE(R"(\s*[\}\]])");
	regex 	arrayRE(R"(\[(.+)\])") ;
    regex   emptyRE(R"(^\s*$)");
	regex   jLineRE(R"(\x22(\w+)\x22\s*: (.*),?)");
	regex   jIntRE(R"(\s*(\d+),?)");	
    regex   jStrRE(R"(\s*\x22(\w+)\x22\s*,?)");
    regex   jBoolorNullRE(R"(\s*(\w+),?)");

   
    smatch	fileTypeMatch;
    smatch  jLineMatch;

    smatch  jValMatch;
    
    string  jsonID;
    string  jsonVal;
   
  
    int     jInt;
    string  jStr;
    bool    jBool;
    string  jNull = "null";    

    bool    openBraceNotFound = true;
	bool    closeBraceNotFound = true;    
    
    JsonObject* 	jObject = new JsonObject();      
    JsonArray *     jArray = new JsonArray();




    do {
        getline(inFile, buf);
        if(regex_search(buf, jLineMatch, emptyRE)) {
            cout << "empty line...\n";
            continue;
            }
        if(regex_search(buf, jLineMatch, openBraceRE)) {
            openBraceNotFound = false;            
                  
            continue;            
            }
        if (openBraceNotFound) {
            cout <<"ERROR expected {...\n";
            exit(1);
            }
            
        if(regex_search(buf, jLineMatch, closeBraceRE)) {
            break; 
            }
        if(regex_search(buf, jLineMatch, jLineRE))
            {
            jsonID = jLineMatch.str(1);
            jsonVal = jLineMatch.str(2);
            }

        else {
            cout << "\nERROR: Not a valid line! \n";
            continue;            
            }
        


        if (regex_search(jsonVal, jValMatch, arrayRE)) {
            cout << "Array matched!\n";
            jArray->Add(new JsonString(jLineMatch.str(1)));
            jObject->Add(jsonID, jArray);
            }
            
        else if (regex_search(jsonVal, jValMatch, jIntRE)) {
            jInt = stoi(jsonVal);

            cout << "Valid Int " << jInt << " matched! \n";
            jObject->Add(jsonID, new JsonNumber(jInt));
            }    
        else if (regex_search(jsonVal, jValMatch, jStrRE)) {
            jStr = jValMatch.str(1);
            cout << "Valid String " << jStr << " matched! \n";
            jObject->Add(jsonID, new JsonString(jStr));
            }
        else if(regex_search(jsonVal, jValMatch, jBoolorNullRE)) {           
            if ("true" == jValMatch.str(1)) {
                jBool = true ;         
                cout << "Valid bool " <<  jBool << " matched! \n";
                jObject->Add(jsonID, new JsonBoolean(jBool));
               
                }
            else if ("false" == jValMatch.str(1)){
                jBool = false ;
                cout << "Valid bool " <<  jBool << " matched! \n";
                jObject->Add(jsonID, new JsonBoolean(jBool));
                }            
           
            else if ("null" == jValMatch.str(1)){
                cout << "Valid null matched! \n";
                jObject->Add(jsonID, new JsonNull());
                }            
            }

        } while (!inFile.eof() && closeBraceNotFound);


	cout << endl << endl ;
    jObject->Print();
	return 0;
}
