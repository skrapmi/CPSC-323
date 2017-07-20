/********************************************************
 * Members: Tim, Luis, Stephen                          *
 * Class:   CS-323 Compilers                            *
 * File:    ast.h                                       *
 * Date:    July 19, 2017                               *
 *******************************************************/


#ifndef AST_H_
#define AST_H_


class JsonValue
{
 public:
  virtual void Print() = 0;
};

class JsonObject : public JsonValue
{
 private:
  map<string, JsonValue*>pairs;

 public:
  virtual void Print();
  void Add(string name, JsonValue* value);
};

class JsonArray : public JsonValue
{
 private:
  list<JsonValue*> values;

 public:
  virtual void Print();
  void Add(JsonValue *v);
};

class JsonString : public JsonValue
{
 private:
  string value;

 public:
  JsonString(string s) : value(s) { };
  virtual void Print();
};

class JsonNumber : public JsonValue
{
 private:
  double value;

 public:
  JsonNumber(double d) : value(d) { };
  virtual void Print();
};

class JsonBoolean : public JsonValue
{
 private:
  bool value;

 public:
  JsonBoolean(bool b) : value(b) { };
  virtual void Print();
};

class JsonNull : public JsonValue
{
 public:
  virtual void Print();
};


#endif // AST_H_
