#ifndef INIFILE_H_
#define INIFILE_H_


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <map>


class IniFile
{
	
	public:
		
		// Overloaded Constructor
		IniFile(std::string filename);
		std::string GetProfileString(std::string section, std::string property_name);
		 // Destructor
  

	private:
        std::map<std::string, std::string> data;	
       
        std::map< std::string, std::map<std::string, std::string>>  map_data;

};


#endif // INIFILE_H_
