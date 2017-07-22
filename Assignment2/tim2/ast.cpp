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
  cout << "\n" << name << " adding: ";
  value->Print();
  cout << endl;

  pairs.insert( std::pair<string, JsonValue*>(name, value) );

  // Test code to see what is in the map
  //cout << "map contains:\n";
  //std::map<string, JsonValue*>::iterator it = pairs.begin();
  //for (it = pairs.begin(); it !=pairs.end(); ++it)
  //  cout << it->first << " => " << it->second << " | ";
 
 // cout << endl;
}

void JsonArray::Add(JsonValue *v){
  // An iterator that points to the list
  std::list<JsonValue *>::iterator it;
  it = values.begin();
  
  // Insert values into the array
  values.insert(it, v);

  // Test code to see what is in the array
  //cout << "list contains:\n";
  //for (it = values.begin(); it != values.end(); ++it)
  //  cout << " " << *it;
  //cout << "\n";
}

void JsonObject::Print(){
	// Test code to see what is in the map
  cout << "map contains:\n";
  std::map<string, JsonValue*>::iterator it = pairs.begin();
  for (it = pairs.begin(); it !=pairs.end(); ++it) {  
    cout << it->first << " => ";
    it->second->Print(); 
    cout << " | ";
    }
  cout << endl;
}

void JsonArray::Print(){
	//need to run a print for all parts of array	
	//for (list<JsonObject>::iterator i = this.value.begin(); i != this.end(); ++i)
    //cout << *i->first << endl;
    // An iterator that points to the list
  std::list<JsonObject *>::iterator it;
   
   // Test code to see what is in the array
  cout << "list contains:\n";
  for (it = values.begin(); it != values.end(); ++it)
    *it->Print(); //cout << " " << **it;
  cout << "\n";
}
void JsonString::Print(){
	//print object string
	cout << "String " << this->value;
}

void JsonNumber::Print(){
	//print object number
	cout << "Number " << this->value;
}

void JsonBoolean::Print(){
	//print object boolean
	cout << "Boolean " << this->value;
}

void JsonNull::Print(){
	cout << "null";
}

