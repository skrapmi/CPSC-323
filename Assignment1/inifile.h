#ifndef INIFILE_H_
#define INIFILE_H_


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>

class IniFile
{
 public:
  IniFile(std::string filename);
  std::string GetProfileString(std::string section, std::string property_name);
};


#endif // INIFILE_H_
