/***********************************************************
 * File:        main.cpp                                   *
 * Description: Main program file. An instance of IniFile  *
 * is allocated in memory, and elements are extracted.     *
 **********************************************************/

#include <iostream>
#include "inifile.h"
using namespace std;

// Begin main function
int main(int argc, char *argv[0]) {
  // Used to store any filename passed as a command argument
  string aFile;

  // Check for a command argument
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <filename>\n";
  } else {
    // store the command argument as the filename
    aFile = argv[1];
  }
  // Create an instance of IniFile and pass the filename from the command line
  IniFile stuff(aFile);

  // Extract elements from the INI file
  cout << stuff.GetProfileString("foo", "bar") << endl;
  cout << stuff.GetProfileString("foo2", "shift") << endl;
  cout << stuff.GetProfileString("second", "shift") << endl;
  cout << stuff.GetProfileString("second", "bar") << endl;

  return 0;
}
