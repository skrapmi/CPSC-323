/****************************************************************************
 *                                                                          *
 * Members: Tim, Luis, Stephen                                              *
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
 * Member function: Custom Constructor                                   *
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

  // Begin do-while loop
  do {
    getline(inFile, buf);

    // Begin try-catch block
    try {
      // regular expression for comment
      regex com(R"(([#;]))");  //(R"(\[([^\]]+))"); 
		
      // regular expression for section
      regex sec(R"(\[(\w+)\])");

      // regular expression for property and value
      regex prop(R"((\w+)=(\w+))");

      // Define smatch variables
      smatch match;
      smatch comMatch;

      if (regex_search(buf, match, sec) && !regex_search(buf, comMatch, com)) {
	secStr = match.str(1);
      }	else if(regex_search(buf, match, prop) && !regex_search(buf, comMatch, com)) {
	propStr = match.str(1);
	valStr = match.str(2);
            
        data[propStr] = valStr; 
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
      cout << "SECTION: " << map_data_it->first << endl;
      data_it = data.begin();
      while(data_it != data.end())
	{
	  cout << "Property: " << data_it->first << endl;
          cout << "Value: " << data_it->second << endl;
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
	return " ";
}

