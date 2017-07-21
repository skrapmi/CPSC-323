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

void JsonObject::Add(std::string name, JsonValue* addVal){
  // Insert values into the map
  cout << "\nadding: ";
  addVal->Print();
  cout << endl;

  pairs.insert( std::pair<string, JsonValue*>(name, addVal) );

  // Test code to see what is in the map
  cout << "map contains:\n";
  std::map<string, JsonValue*>::iterator it = pairs.begin();
  for (it = pairs.begin(); it !=pairs.end(); ++it)
    cout << it->first << " => " << it->second << " | ";
 
  cout << endl;
}

void JsonArray::Add(JsonValue *v){
  // An iterator that points to the list
  std::list<JsonValue *>::iterator it;
  it = values.begin();
  
  // Insert values into the array
  values.insert(it, v);

  // Test code to see what is in the array
  cout << "list contains:\n";
  for (it = values.begin(); it != values.end(); ++it)
    cout << " " << *it;
  cout << "\n";
}

void JsonObject::Print(){
	//need to call print from other object parts
}

void JsonArray::Print(){
	//need to run a print for all parts of array	
}
void JsonString::Print(){
	//print object string
}

void JsonNumber::Print(){
	//print object number
    cout << value;
}

void JsonBoolean::Print(){
	//print object boolean
}



