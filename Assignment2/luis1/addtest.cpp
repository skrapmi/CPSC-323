/******************************************************************
 * Members: Tim, Luis, Stephen                                    *
 * Class:   CS-323 Compilers                                      *
 * Project: Assignment 2 - JSON Parser                            *
 * File:    main.cpp                                              *
 * Date:    July 19,2017                                          *
 *****************************************************************/


#include <iostream>
#include <fstream>
#include "ast.h"
#include <regex>

using namespace std;


int main() {


    JsonObject* o = new JsonObject();
    o->Add("str", new JsonString("foo"));
    o->Add("num", new JsonNumber(123));
    o->Add("bool", new JsonBoolean(true));
    //o->Add("nul", new JsonNull());
    
    JsonArray *a = new JsonArray();
    a->Add(new JsonString("bar"));
    a->Add(new JsonNumber(456));
    a->Add(new JsonBoolean(false));
    o->Add("arr", a);



	
	return 0;
}
