#ifndef _GENERICTYPEWRAPPER_H
#define _GENERICTYPEWRAPPER_H

#include <string>

enum GenericType {GENERIC, INTEGER, DOUBLE, STRING, BOOL};

struct Generic {
    virtual GenericType type() const;
    static Generic* wrapPrimitive(std::string data);
};

struct Integer : public Generic {
    int data;
    Integer(int data) : data(data) {}
    GenericType type() const;
};

struct Double : public Generic {
    double data;
    Double(double data) : data(data) {}
    GenericType type() const;
};

struct String : public Generic {
    std::string data;
    String(std::string data) : data(data) {}
    GenericType type() const;
};

struct Bool : public Generic {
    bool data;
    Bool(bool data) : data(data) {}
    GenericType type() const;
};

#endif

