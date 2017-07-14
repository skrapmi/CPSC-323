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
		// Default Constructor
		IniFile();
		// Overloaded Constructor
		IniFile(std::string filename);
		std::string GetProfileString(std::string section, std::string property_name);
		 // Destructor
  	~IniFile();

	private:
		bool getKey(std::string keyBuf);
		std::map< std::string,std::map<std::string,std::string> > map_data;
		std::map<std::string, std::string> data;
		std::string secStr;
    bool firstUse = true;

};


#endif // INIFILE_H_
