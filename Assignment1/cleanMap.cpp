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
//IniFile::IniFile();
//IniFile::IniFile(std::string filename);
//string IniFile::GetProfileString(string section, string property_name);
//bool getKey(string keyBuf);





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
    std::map< std::string, std::map<std::string, std::string>>::iterator it;
    std::map<std::string, std::string>::iterator it2;
    string      secStr;
    string      propStr;
	string	    valStr;
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
  

	do {
		getline(inFile, buf);
	
    try {
        // regular expression for comment
        regex com(R"(([#;]))");  //(R"(\[([^\]]+))"); 
		
        // regular expression for section
        regex sec(R"(\[(\w+)\])");

        // regular expression for property and value
        regex prop(R"((\w+)=(\w+))");
	
        smatch match;
        smatch comMatch;

        if (regex_search(buf, match, sec) && !regex_search(buf, comMatch, com)) {
			secStr = match.str(1);
             
		    } 

		else if(regex_search(buf, match, prop) && !regex_search(buf, comMatch, com)) {
            propStr = match.str(1);
			valStr = match.str(2);
            
            data[propStr] = valStr; 
            map_data[secStr] = data;
            }           
        } 
        
    
    catch (regex_error& e) {
            // Syntax error in the RE
            cout << "Error.\n";
            }
	
	} while(!inFile.eof());

    it = map_data.begin();
     
    cout << "\n ======MAP=========\n";
    while(it != map_data.end())
        {
        cout << "SECTION: " << it->first << endl;
        it2 = data.begin();
        while(it2 != data.end())
            {
            cout << "Property: " << it2->first << endl;
            cout << "Value: " << it2->second << endl;
            it2++;
            }               
        it++;
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

