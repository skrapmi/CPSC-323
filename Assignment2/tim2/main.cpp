/******************************************************************
 * Members: Tim Parks, Luis, Stephen                              *
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
	int 	lineNum = 1;
	string  buf;
	bool 	isArrayType = false;
	bool	isArrayClosed = false;
	bool	isLabel = false;
	bool	checkLine	= true;
	
	regex storageStart(R"(\s*(\{))");
	regex storageEnd(R"(\s*(\}))");
	regex lbl(R"(\s+\x22(\w+)\x22:)");
	regex str(R"(\s+\x22(\w+)\x22\W+)");
	regex num(R"(\s+(\d+)\W+)");	
	regex bol(R"(\s+(\w+)\W+)"); 	
	
	smatch lblMatch;
	smatch storMatch;

	JsonObject*  o = new JsonObject();  //Pointer to JsonObject - String, Number, Boolean, Null 
	JsonArray*   a = new JsonArray();	//Pointer to JsonArray  - Array of String, Number, Null 
	
	//check for proper file declaration of type
	try{
		getline(file, buf);
		if(regex_search(buf, storMatch, storageStart))	
			lineNum++;
		else{
			cout << "Invalid JSON storage file, missing { on line 1.  Please check file!\n\n";
			exit(1);
		}
	}
	catch(regex_error& e){
		cout << "Regular expression Error";
		exit(1);
	}
	
	char c;					//read file
	char parseArray[1024];	//char array
	int  parseInt = 0;		//placehooder in file
	string labelHold;		//temp storeage
	parseArray[0] = 0x00;

	while(file.get(c)){
		smatch strMatch;
		if(c == '\n'){
			checkLine = true;
			if(parseInt != 0){
				cout << "Parse Error on line " << lineNum << endl;
				exit(1);
			}
			lineNum++;
		}
		else if(c == '['){
			isArrayType = true;	
			parseInt = 0;
		}
		else if(c == '}'){
			//cout << "File parsing complete!" << endl;  //Error Checking Output
			break;
		}
		else if(c == ']'){
			if(isLabel)
				o->Add(labelHold,a);
			isArrayClosed = true;
			isArrayType = false;
			checkLine = false;
		}
		else if(checkLine){		//skips processing until next line of file, if false
			parseArray[parseInt++] = c;
			parseArray[parseInt] = 0x00;  //Null terminated char array
			string parseStr(parseArray);
			if(!isLabel && !isArrayType){
				if(regex_search(parseStr, lblMatch, lbl)){
					labelHold = lblMatch.str(1);
					parseInt = 0;
					isLabel = true;
				}
			}
			else{
				if(regex_search(parseStr, strMatch, str)){
					parseInt = 0;
					if(isLabel && !isArrayType){
						o->Add(labelHold,new JsonString(strMatch.str(1))); 
						checkLine = false;
						isLabel = false;
					}
					else
						a->Add(new JsonString(strMatch.str(1))); 					
				}
				else if(regex_search(parseStr, strMatch, num)){
					parseInt = 0;
					//cout << "found number " << stoi(strMatch.str(1)) << endl;
					if(isLabel && !isArrayType){
						o->Add(labelHold,new JsonNumber(stoi(strMatch.str(1))));
						checkLine = false;
						isLabel = false;
					}
					else
						a->Add(new JsonNumber(stoi(strMatch.str(1))));					
				}
				else if(regex_search(parseStr, strMatch, bol)){
					
					//cout << "found bool " << strMatch.str(1) << endl;
					
					if(strMatch.str(1) == "true"){
						parseInt = 0;
						if(isLabel && !isArrayType){
							o->Add(labelHold,new JsonBoolean(true));
							checkLine = false;
							isLabel = false;
						}
						else
							a->Add(new JsonBoolean(true));
					}
					else if(strMatch.str(1) == "false"){
						parseInt = 0;
						if(isLabel && !isArrayType){
							o->Add(labelHold,new JsonBoolean(false));
							checkLine = false;
							isLabel = false;
						}
						else
							a->Add(new JsonBoolean(false));
					}
					else if(strMatch.str(1) == "null"){
						parseInt = 0;
						if(isLabel){
							o->Add(labelHold,new JsonNull());
							checkLine = false;
							isLabel = false;
						}
						else{
							cout << "Parse error: expect true, false, or null at " << lineNum << ":" << parseInt << endl;
							exit(1);
						}
					}
				}
			}
		}
	}
	if(isLabel)
		o->Print();
	else
		a->Print();
		
}

