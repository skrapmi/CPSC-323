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
IniFile::IniFile(string filename)
{
   // Define a variable to read in an INI file
    ifstream inFile;
    string buf;

    // Iterators for the maps
    map< string, map<string, string>>::iterator map_data_it;
    map<string, string>::iterator data_it;

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
        } 
    else {
        // The file was successfully opened
        cout << "File opened successfully.\n\n";
        }

    // regular expression for comment, section, property and value
    regex   com(R"(([#;]))"); 
    regex   sec(R"(\[(\w+)\])");
    regex   prop(R"((\w+)\s*=\s*(\w+))");

    // Define smatch variables
    smatch  secMatch;
    smatch  propMatch;
    smatch  comMatch;   
    
    //define booleans for matches
    bool    sectionFound;
    bool    propertyFound;    
    bool    commentNotFound;
    // Begin do-while loop
    do {
        getline(inFile, buf);  
        // Begin try-catch block
        try {
            
            sectionFound  = regex_search(buf, secMatch, sec);
            propertyFound = regex_search(buf, propMatch, prop); 
            commentNotFound  = !regex_search(buf, comMatch, com);
            // Checks for RE matching Section and ignors the rest
            if(sectionFound && commentNotFound) { 
	            secStr = secMatch.str(1);
       	        data.clear();
                }  
	        //check for empty map before navigation
            else if(propertyFound && commentNotFound) {
       	        if(!map_data.empty()){
	                map_data_it = map_data.begin();
	                // While If block to reset data for additional properties in same section
	                while((map_data_it != map_data.end())){
	                    if(map_data_it->first == secStr){
	                        data.clear();
	                        data = map_data_it->second;
	                        map_data.erase(map_data_it);
	                        break;
	                        }
	                    map_data_it++;
	                    }
	                }		
       	        propStr = propMatch.str(1);
	            valStr = propMatch.str(2);
		
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
    while(map_data_it != map_data.end()){
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
string IniFile::GetProfileString(string section, string property_name)
{
    // Iterators for the maps
    map< string, map<string, string>>::iterator map_data_it;
    map<string, string>::iterator data_it;
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
    return (secFound) ?  "Not a valid property of section: " + section 
                      : "Section " + section + " not found";

}

