#ifndef AST_H_
#define AST_H_


#include <list>
#include <map>


class JsonValue
{
    public:
        virtual void Print() = 0;
};

class JsonObject : public JsonValue
{
    private:
        std::map<std::string, JsonValue*> pairs;

    public:
        virtual void Print();
        void Add(std::string name, JsonValue* value);
};

class JsonArray : public JsonValue
{
    private:
        std::list<JsonValue*> values;

    public:
        virtual void Print();
        void Add(JsonValue *v);
};

class JsonString : public JsonValue
{
    private:
        std::string value;

    public:
        JsonString(std::string s) : value(s) { };
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

//void Print() : public JsonValue{};

#endif // AST_H_
