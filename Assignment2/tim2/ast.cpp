/******************************************************************
 * Members: Tim Parks, Luis, Stephen                              *
 * Class:   CS-323 Compilers                                      *
 * Project: Assignment 2 - JSON Parser                            *
 * File:    ast.cpp                                               *
 * Date:    July 19, 2017                                         *
 *****************************************************************/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include "ast.h"


using namespace std;

void JsonObject::Add(std::string name, JsonValue* value){
	// Insert values into the map

	pairs.insert( std::pair<string, JsonValue*>(name, value) );
}

void JsonArray::Add(JsonValue *v){
	// An iterator that points to the list
	std::list<JsonValue *>::iterator it;
	it = values.begin();

	// Insert values into the array
	values.insert(it, v);
}

void JsonObject::Print(){
	// Test code to see what is in the map
	std::map<string, JsonValue*>::iterator it = pairs.begin();

	for (it = pairs.begin(); it !=pairs.end(); it++){
		cout << it->first << " ";
		it->second->Print(); 
	}
	cout << endl;
}

void JsonArray::Print(){
	std::list<JsonValue*>::iterator it = values.begin();
   	cout << "( object ";
   	// Test code to see what is in the array
  	for (it = values.begin(); it != values.end(); it++)
    	(*it)->Print();
	cout << ") ";
}

void JsonString::Print(){
	//print object string
    cout <<  "( string " << value << " ) ";
}

void JsonNumber::Print(){
	//print object number
    cout << "( number " << value << " ) ";
}

void JsonBoolean::Print(){
	//print object boolean
    cout << "( boolean ";
    (value) ? cout << "true" : cout << "false";
    cout << " ) ";
}

void JsonNull::Print(){
	//print object number
    cout << "( null ) ";
}

