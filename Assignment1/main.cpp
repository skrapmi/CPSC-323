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
	cout << stuff.GetProfileString("foo", "bar") << endl;
  cout << stuff.GetProfileString("foo2", "shift") << endl;
	cout << stuff.GetProfileString("second", "shift") << endl;
	cout << stuff.GetProfileString("second", "bar") << endl;

  return 0;
}
