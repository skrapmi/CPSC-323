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
	bool	isLabelType = false;
	bool	checkLine	= true;
	
	regex storageStart(R"(\s*(\{))");
	regex storageEnd(R"(\s*(\}))");
	regex lbl(R"(\s*\x22(\w+)\x22\s*:)");
	regex str(R"(\s*\x22(\w+)\x22\s*,*)");
	regex num(R"(\s*(\d+)\W+)");		
	regex bol(R"(\s+(\w+)\W+)");
	
	
	smatch lblMatch;
	smatch storMatch;

	JsonObject*  o = new JsonObject();  //Pointer to JsonObject - String, Number, Boolean, Null or Array
	JsonArray*   a = new JsonArray();	//Pointer to JsonArray
	
	try{
		getline(file, buf);
		regex_search(buf, storMatch, storageStart);
		lineNum++;
	}
	catch(regex_error& e){
		cout << "Invalid JSON storage file, missing { on line 1.  Please check file!\n\n";
		exit(1);
	}
	
	char c;
	char parseArray[1024];
	int  parseInt = 0;
	string labelHold;
	parseArray[0] = 0x00;

	while(file.get(c)){
		smatch strMatch;
		if(c == '\n'){
			lineNum++;
			parseInt = 0;
			checkLine = true;
			/*if(parseInt != 0){
				cout << "Parse Error at " << lineNum << ":" << parseInt <<  endl;
				exit(1);
			}*/
		}
		else if(c == '['){
			isArrayType = true;	
			parseInt = 0;
		}
		else if(c == '}'){
			cout << "File parsing complete!" << endl;
			break;
		}
		else if(c == ']'){
			if(isArrayType)
				o->Add(lblMatch.str(1),a);
			isArrayClosed = true;
			isArrayType = false;
			checkLine = false;
			parseInt = 0;
		}
		else if(checkLine){		//skips processing until next line of file, if false
			parseArray[parseInt++] = c;
			parseArray[parseInt] = 0x00;  //Null terminated char array
			string parseStr(parseArray);
			//cout << parseInt << " " << parseStr << endl;
			if(!isLabelType && !isArrayType){
				if(regex_search(parseStr, lblMatch, lbl)){
					labelHold = lblMatch.str(1);
					//cout << "Labal found " << lblMatch.str(1) << endl;  //error checking
					parseInt = 0;
					isLabelType = true;
				}
			}
			else{
				//cout << lblMatch.str(1) << endl;
				if(regex_search(parseStr, strMatch, str)){
					//cout << lblMatch.str(1) << "found string " << strMatch.str(1) << endl;
					if(isLabelType && !isArrayType){
						o->Add(labelHold,new JsonString(strMatch.str(1))); 
						checkLine = false;
						isLabelType = false;
					}
					else
						a->Add(new JsonString(strMatch.str(1))); 
					
					parseInt = 0;
				}
				else if(regex_search(parseStr, strMatch, num)){
					parseInt = 0;
					//cout << "found number " << stoi(strMatch.str(1)) << endl;
					if(isLabelType && !isArrayType){
						o->Add(labelHold,new JsonNumber(stoi(strMatch.str(1))));
						checkLine = false;
						isLabelType = false;
					}
					else
						a->Add(new JsonNumber(stoi(strMatch.str(1))));					
				}
				else if(regex_search(parseStr, strMatch, bol)){
					parseInt = 0;
					//cout << "found bool " << strMatch.str(1) << endl;
					
					if(strMatch.str(1) == "true"){
						if(isLabelType && !isArrayType){
							o->Add(labelHold,new JsonBoolean(true));
							checkLine = false;
							isLabelType = false;
						}
						else
							a->Add(new JsonBoolean(true));
					}
					else if(strMatch.str(1) == "false"){
						if(isLabelType && !isArrayType){
							o->Add(labelHold,new JsonBoolean(false));
							checkLine = false;
							isLabelType = false;
						}
						else
							a->Add(new JsonBoolean(false));
					}
					else if(strMatch.str(1) == "null"){
						if(isLabelType){
							o->Add(labelHold,new JsonNull());
							checkLine = false;
							isLabelType = false;
						}
						else{
							cout << "Parse error: expect true, false, or null at " << lineNum << ":" << parseInt << endl;
							exit(1);
						}
					}
				}
			}
			/*if(isArrayClosed && isLabelType){
				o->Add(lblMatch.str(1), a);
				checkLine = false;
				isLabelType = false;
			}
			else if(isArrayType && v){
				a->Add(*v);
				*v = NULL;
			}
			else if(isLabelType && v){
				o->Add(lblMatch.str(1), *v);
				*v = NULL;
				checkLine = false;
				isLabelType = false;
			}*/		
			
		}
	}
	if(isLabelType)
		o->Print();
	else
		a->Print();
		
}


/*

bool    strFound 	= false;
bool    numFound 	= false;    
bool    bolFound	= false;
bool	arrFound	= false;
bool 	storFound 	= false;

regex str(R"(\s+\x22(\w+)\x22:\s+\x22(\w+)\x22)");
regex num(R"(\s+\x22(\w+)\x22:\s+(\d+))");		
regex bol(R"(\s+\x22(\w+)\x22:\s+(\w+))");
regex arr(R"(\s+\x22(\w+)\x22:\s+\[\s*(.+)\s*\])");
regex all(R"(\s+\x22(\w+)\x22:\s+(\x22(\w+)\x22|(\d+)|(\w+)|\[\s*(.+)\s*\])");

lineNum++;
		getline(file, buf);
		try {
			regex_search(buf, labelMatch, lbl);
			//strFound = regex_search(buf, strMatch, str);
			//numFound = regex_search(buf, numMatch, num); 
      //bolFound = regex_search(buf, bolMatch, bol);
			//arrFound = regex_search(buf, arrMatch, arr);
			//storFound = regex_search(buf, storMatch, storageEnd);
			if(regex_search(buf, arrMatch, arr){
				isArrayType = true;
			}
			else
	    if (regex_search(buf, strMatch, str) && !isArrayType) {
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
*/
