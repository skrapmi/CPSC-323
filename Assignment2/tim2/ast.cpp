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
	//pairs.insert(name, value);
}

void JsonArray::Add(JsonValue *v){
	//values.insert(v);
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
}

void JsonBoolean::Print(){
	//print object boolean
}



