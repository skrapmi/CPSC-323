#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
using namespace std;


bool getKey(string buf);

int main() 
{
    ifstream    inFile; // Define a variable to read in a .ini file
    string      buf;
    
    // Read in a .ini file
    inFile.open("test.ini");

    // Check that the file was opened successfully
    if (inFile.fail( )) {
        // Print an error message
        cout << "Error opening file.\n\n";
        exit(1);
        } 
    
    else {
        // The file was successfully opened
        cout << "File opened successfully.\n\n";
        }
    

	do {
		getline(inFile, buf);
		//cout << buf << endl;
		
		getKey(buf);
		} while(!inFile.eof());
 
    // Close the file
    inFile.close();
  
    return 0;
}

bool getKey(string keyBuf)
{
    bool		retVal = false;
    string      secStr;
	string      propStr;
	string	    valStr;
    
    try {
        // regular expression for comment
        regex com(R"(([#;]))");  //(R"(\[([^\]]+))"); 
		
        // regular expression for section
        regex sec(R"(\[(\w+)\])");

        // regular expression for property and value
        regex prop(R"((\w+)=(\w+))");
	
        smatch match;
        smatch comMatch;

        if (regex_search(keyBuf, match, sec) && !regex_search(keyBuf, comMatch, com)) {
			secStr = match.str(1);
			cout << "\nSECTION: " << secStr << endl;
            cout << "matches: " << match.size() << endl;
            retVal = true;			    
		    } 

		else if(regex_search(keyBuf, match, prop) && !regex_search(keyBuf, comMatch, com)) {
            propStr = match.str(1);
			valStr = match.str(2);
			cout << "PROPERTY : "<< propStr << endl;    
			cout << "VALUE    : " << valStr << endl;		
		    retVal = true;
            }
        } 
    
    catch (regex_error& e) {
            // Syntax error in the RE
            cout << "Error.\n";
            }
	
	return retVal;
}

