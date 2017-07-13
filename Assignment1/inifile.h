#ifndef INIFILE_H_
#define INIFILE_H_


class IniFile
{
 public:
  IniFile(string filename);
  string GetProfileString(string section, string property_name);
};


#endif // INIFILE_H_
