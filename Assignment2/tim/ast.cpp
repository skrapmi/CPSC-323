/******************************************************************
 * Members: Tim, Luis, Stephen                                    *
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
	pairs.insert(name, value);
}

void JsonArray::Add(JsonValue *v){
	values.insert(v);
}

//virtual void JsonObject::Print(){};
// Begin function definitions


