#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include "inifile.h"
using namespace std;




int main() {

	IniFile stuff("test.ini");
	cout << stuff.GetProfileString("foo", "bar");

}
