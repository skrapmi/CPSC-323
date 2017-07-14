/***********************************************************
 * File:        main.cpp                                   *
 * Description: Main program file. An instance of IniFile  *
 * is allocated in memory, and elements are extracted.     *
 **********************************************************/

#include <iostream>
#include "inifile.h"
using namespace std;

// Begin main function
int main() {
  // Create an instance of IniFile
  IniFile stuff("test.ini");

  // Extract elements from the INI file
  cout << stuff.GetProfileString("foo", "bar");

  return 0;
}
