<<<<<<< HEAD
Assignment 2

psuedo code! 
// first check if the file is an object or array

regex	objectRE("\{regular Expression for Object}");
regex	arrayRE("\[ regular Expression for array\]");

cmatch	fileTypeMatch;

// if this bool is true than the file is Valid object
   if false then the file is valid array
bool	isObjectOrArray; 

// if the call to reg_search is true than the file is a valid Object 
if (isObjectOrArray = reg_search(buf, fileTypeMatch, objectRE){
	
	// define a JsonObject
	JsonObject* jObject = new JsonObject();
	}

// if the call is false than check for valid array 
// and assign isObjectOrArray to false
else if(isObjectOrArray = !reg_search(buf, fileTypeMatch, arrayRE));
	
	// define a JsonArray
	JsonArray *jArray = newJsonArray();
	}

// if not valid object or array 
else {
	// not valid object or array
	// exit program, not valid file
	}

do {
	getline(inFile, buf);
	
	regex	jLineRE("(capture ID) : (capture Value)");
	cmatch	jLineMatch;
	
	bool isValidLine = regex_search( buf, jLineMatch, jlineRE);
	
	
	string 	jsonID 	= jLineMatch.str(1); 
	string	jsonVal = jLineMatch.str(2);	
	


	//if an valid data type is matched  add to object or Array
	if(regex_search(match an Int)) {
		(isObjectorArray) ? jObject->Add() : jArray->Add();
		}
	
	else if(regex_search(match an string)) {
		(isObjectorArray) ? jObject->Add() : jArray->Add();
		}
	
	else if(regex_search(match a bool)) {
		(isObjectorArray) ? jObject->Add() : jArray->Add();
		}
	
	else if(regex_search(match a Null)) {
		(isObjectorArray) ? jObject->Add() : jArray->Add();
		}
	
	// at this point a valid data type, including Identifier and 
	// value has been added to an Object or Array
	} while (!inFile.eof() // end of while
=======
Assignment 2 : JSON Parser
Members: Tim, Luis, Stephen
