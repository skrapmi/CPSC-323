#ifndef INIFILE_H_
#define INIFILE_H_


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <map>

 struct propVal{
                std::string  property = "";
                std::string   value = "" ;
		        };

class IniFile
{
	
	public:
		
		// Overloaded Constructor
		IniFile(std::string filename);
		std::string GetProfileString(std::string section, std::string property_name);
		 // Destructor
  

	private:
		bool getKey(std::string keyBuf);
       // propVal        data;
        std::map<std::string, std::string> data;	
        //std::map< std::string,std::map<std::string,std::string> > map_data = {"", data};
       
        std::map< std::string, std::map<std::string, std::string>>  map_data;
	//	std::string secStr;

};


#endif // INIFILE_H_
