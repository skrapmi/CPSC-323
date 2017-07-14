/****************************************************************************
 *                                                                          *
 * Members: Timothy Parks, Luis Gonzalez, Stephen Cordasco                  *
 * Class:   CS-323 Compilers                                                *
 * Project: Scanning INI files                                              *
 * Date:    July 12, 2017                                                   *
 * File:    inifile.cpp                                                     *
 * Desc:    File defines all member functions from IniFile class.           *
 *                                                                          *
 ***************************************************************************/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <map>
#include "inifile.h"


using namespace std;


/*****************************************************************************
 * Member function: Custom Constructor                                       *
 * Parameters: string filename                                               *
 * Description: Initializes an IniFile object by reading in the filename and *
 *              opening the .ini file. All tokens in the file are scanned.   *
 ****************************************************************************/
IniFile::IniFile(std::string filename)
{
   // Define a variable to read in an INI file
  ifstream inFile;
  string buf;

  // Iterators for the maps
  std::map< std::string, std::map<std::string, std::string>>::iterator map_data_it;
  std::map<std::string, std::string>::iterator data_it;

  // Strings to store SECTIONS, PROPERTIES, and VALUES
  string secStr;
  string propStr;
  string valStr;
  
  // Read in a .ini file
  inFile.open(filename);

  // Check that the file was opened successfully
  if (inFile.fail( )) {
    // Print an error message
    cout << "Error opening file.\n\n";
    exit(1);
  } else {
    // The file was successfully opened
    cout << "File opened successfully.\n\n";
  }

  // regular expression for comment
  regex com(R"(([#;]))"); 
		
  // regular expression for section
  regex sec(R"(\[(\w+)\])");

  // regular expression for property and value
  regex prop(R"((\w+)\s*=\s*(\w+))");

  // Define smatch variables
  smatch match;
  smatch comMatch;   


  // Begin do-while loop
  do {
    getline(inFile, buf);  
    // Begin try-catch block
    try {
      // Checks for RE matching Section and ignors the rest
      if (regex_search(buf, match, sec) && !regex_search(buf, comMatch, com)) {
	secStr = match.str(1);
       	data.clear();
	// Checks for RE matching Property/Value combo and ignors the rest
      }	else if(regex_search(buf, match, prop) && !regex_search(buf, comMatch, com)) {
	//check for empty map before navigation
       	if(!map_data.empty()){
	  map_data_it = map_data.begin();
	  // While If block to reset data for additional properties in same section
	  while(map_data_it != map_data.end()){
	    if(map_data_it->first == secStr){
	      data.clear();
	      data = map_data_it->second;
	      map_data.erase(map_data_it);
	      break;
	    }
	    map_data_it++;
	  }
	}		
       	propStr = match.str(1);
	valStr = match.str(2);
		
       	// All past and current properties/values mapped and written to data
        data[propStr] = valStr; 
        // data now linked to a single section
        map_data[secStr] = data;
      }
    }
    catch (regex_error& e) {
      // Syntax error in the RE
      cout << "Error.\n";
    } // End try-catch block
	
  } while(!inFile.eof()); // End do-while loop
	
  // Set the map_data iterator to the beginning of the map
  map_data_it = map_data.begin();

  cout << "\n ======MAP=========\n";
  while(map_data_it != map_data.end())
    {
      cout << "\n  SECTION: " << map_data_it->first << endl;
      data = map_data_it->second;
      data_it = data.begin();
      while(data_it != data.end())
	{
	  cout << " Property: " << data_it->first << endl;
       	  cout << "    Value: " << data_it->second << endl;
	  data_it++;
       	}
      map_data_it++;
    }
  
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
  // Iterators for the maps
  std::map< std::string, std::map<std::string, std::string>>::iterator map_data_it;
  std::map<std::string, std::string>::iterator data_it;
  // Initialize the tracking of section found or not
  bool secFound = false;
  // Set the map_data iterator to the beginning of the map
  map_data_it = map_data.begin();
  // While If While If - to find and return the requested value
  while(map_data_it != map_data.end()) {
    if(map_data_it->first == section) {
      secFound = true;
      data = map_data_it->second;
      data_it = data.begin();
      while(data_it != data.end()) {
	if(data_it->first == property_name)
	  return data_it->second;
	data_it++;
      }
    }
    map_data_it++;
  }
  //Output for not found section or properties
  if(secFound)
    return "Not a valid property of section: " + section;
  else
    return "Section " + section + " not found";
}

