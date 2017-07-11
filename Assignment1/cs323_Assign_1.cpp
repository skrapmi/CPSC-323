#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
using namespace std;
// Luis Gonzalez

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

  // Use regex to match a string against the section RE
  string result;
  try {
    std::regex re("\\[(\\w+)\\]\\s+((\\w+)=(\\w+)\\s+)+");  // "name=(.*)"
    std::smatch match;
    if (std::regex_search(subject, match, re) && match.size() > 1) {
			cout << "SECTION \t" << match.str(1);
			cout << "\nPROPERTY \t" << match.str(3);
			cout << "\nVALUE \t\t"  << match.str(4);      
			result = match.str(0);
			//cout << match.size();   //Check the amount of strings returned
    } else {
      result = "";
    }
  } catch (std::regex_error& e) {
    // Syntax error in the RE
    cout << "Error.\n";
  }

  // 

  // Print results
  cout << "\n\nResult: \n" << result << "\n\n";
	
  // Close the file
  inFile.close();


  return 0;
}
