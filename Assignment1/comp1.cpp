/****************************************************************************
 *                                                                          *
 * Members: Tim, Luis, Stephen                                              *
 * Class:   CS-323 Compilers                                                *
 * Project: Scanning INI files                                              *
 * Date:    July 12, 2017                                                   *
 *                                                                          *
 ***************************************************************************/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <map>
#include "inifile.h"


using namespace std;


// Member function prototypes
IniFile::IniFile();
IniFile::IniFile(std::string filename);
string IniFile::GetProfileString(string section, string property_name);
bool getKey(string keyBuf);


/****************************************************************************
 * Member function: Default Constructor                                     *
 * Parameters: none                                                         *
 * Description: Default constructor (assists with memory allocation)        *
 ***************************************************************************/
IniFile::IniFile() {
  // Default constructor
  
}


/*****************************************************************************
 * Member function: Overloaded Constructor                                   *
 * Parameters: string filename                                               *
 * Description: Initializes an IniFile object by reading in the filename and *
 *              opening the .ini file. All tokens in the file are scanned.   *
 ****************************************************************************/
IniFile::IniFile(std::string filename)
{
	ifstream    inFile; // Define a variable to read in a .ini file
  string      buf;
  
  // Read in a .ini file
  inFile.open("test.ini");

  // Check that the file was opened successfully
  if (inFile.fail( )) {
      // Print an error message
      cout << "Error opening file.\n\n";
      exit(1);
      } 
  
  else {
      // The file was successfully opened
      cout << "File opened successfully.\n\n";
      }
  

	do {
		getline(inFile, buf);
		//cout << buf << endl;
	
		getKey(buf);
	} while(!inFile.eof());
 
	// Close the file
	inFile.close();
}


/****************************************************************************
 * Member function: GetProfileString                                        *
 * Parameters: string section, string property_name                         *
 * Description: Returns the value of the section and property.              *
 ***************************************************************************/
string IniFile::GetProfileString(std::string section, std::string property_name)
{
	return " ";
}


/****************************************************************************
 * Local function: getKey                                                   *
 * Parameters: string keyBuff                                               *
 * Description: Uses regular expressions to retrieve specific tokens or     *
 *              sets of tokens from the INI file.                           *
 ***************************************************************************/
bool getKey(string keyBuf)
{
    bool		retVal = false;
    string      secStr;
	string      propStr;
	string	    valStr;
    
    try {
        // regular expression for comment
        regex com(R"(([#;]))");  //(R"(\[([^\]]+))"); 
		
        // regular expression for section
        regex sec(R"(\[(\w+)\])");

        // regular expression for property and value
        regex prop(R"((\w+)=(\w+))");
	
        smatch match;
        smatch comMatch;

        if (regex_search(keyBuf, match, sec) && !regex_search(keyBuf, comMatch, com)) {
			secStr = match.str(1);
			cout << "\nSECTION: " << secStr << endl;
            cout << "matches: " << match.size() << endl;
            retVal = true;			    
		    } 

		else if(regex_search(keyBuf, match, prop) && !regex_search(keyBuf, comMatch, com)) {
            propStr = match.str(1);
			valStr = match.str(2);
			cout << "PROPERTY : "<< propStr << endl;    
			cout << "VALUE    : " << valStr << endl;		
		    retVal = true;
            }
        } 
    
    catch (regex_error& e) {
            // Syntax error in the RE
            cout << "Error.\n";
            }
	
	return retVal;
}


/****************************************************************************
 * Member function: Destructor                                              *
 * Parameters: none                                                         *
 * Description: Responsible for memory deallocation.                        *
 ***************************************************************************/
IniFile::~IniFile() {
  // Destructor
  
}

