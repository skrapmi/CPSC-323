#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
using namespace std;
// Luis Gonzalez

bool getKey(string buf);

int main() {
  // Define a variable to read in a .ini file
  ifstream inFile;

  // Read in a .ini file
  inFile.open("test.ini");

  // Check that the file was opened successfully
  if (inFile.fail( )) {
    // Print an error message
    cout << "Error opening file.\n\n";
    exit(1);
  } else {
    // The file was successfully opened
    cout << "File opened successfully.\n\n";
  }
/*
  // Scan the contents of the .ini file
  char next;
  string subject = "";
  inFile.get(next);
  while (! inFile.eof( )) {
    // Print the contents to the screen
    cout << next;
    subject += next;
    inFile.get(next);
  }

  // Skip a couple lines
  cout << "\n\n";
*/

	string buf = "";

	do {
		getline(inFile, buf);
		cout << buf << endl;
		
		getKey(buf);
		} while(!inFile.eof());
  // Use regex to match a string against the section RE
 
  // Close the file
  inFile.close();


  return 0;
}

bool getKey(string buf)
{
	bool		retVal = false;
  string secStr;
	string propStr;
	string	valStr;
  try {
    std::regex sec(R"(\[([^\]]+))");
		std::regex prop(R"((\w+)=(\w+))");
	
    std::smatch match;
    if (std::regex_search(buf, match, sec) && match.size() > 1) {
			secStr = match.str(1);
			cout << "\nSECTION: " << secStr << endl;   //Check the amount of strings returned
			    
		} 


		else if(std::regex_search(buf, match, prop) && match.size() > 1) {
      propStr = match.str(1);
			valStr = match.str(2);
			cout << "\nPROPERTY: "<< propStr << endl;    
			cout << "\nVALUE: " << valStr << endl;		
		}
  } catch (std::regex_error& e) {
    // Syntax error in the RE
    cout << "Error.\n";
  }
	



	return retVal;
}

