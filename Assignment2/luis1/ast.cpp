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
  pairs.insert( std::pair<string, JsonValue*>(name, addVal) );

}

void JsonArray::Add(JsonValue *v){
  // An iterator that points to the list
  std::list<JsonValue *>::iterator it;
  it = values.begin();


  // Insert values into the array
  values.insert(it, v);

}

void JsonObject::Print(){
	//need to call print from other object parts
  
  std::map<string, JsonValue*>::iterator it = pairs.begin();
  cout << "( object( ";
  for (it = pairs.begin(); it !=pairs.end(); ++it) {   
    cout << it->first << " " ;
    it->second->Print(); 
    }
  cout << ") \n ";
}

void JsonArray::Print(){
	//need to run a print for all parts of array	
  // An iterator that points to the list
  std::list<JsonValue *>::iterator it;
  it = values.begin();

  for (it = values.begin(); it != values.end(); ++it){
    cout << "( " << *it << " ) "; 
    }
}
void JsonString::Print(){
	//print object string
    cout <<  " (string  " << value << ") ";
}

void JsonNumber::Print(){
	//print object number
    cout << "(number " << value << ") ";
}

void JsonBoolean::Print(){
	//print object boolean
    cout << "(boolean ";
    (value) ? cout << "true" : cout << "false";
    cout << ") ";
}

void JsonNull::Print(){
	//print object number
    cout << "(null) ";
}


