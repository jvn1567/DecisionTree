#ifndef _GENERICTYPEWRAPPER_H
#define _GENERICTYPEWRAPPER_H

#include <string>

enum GenericType {GENERIC, INTEGER, DOUBLE, STRING, BOOL};

struct Generic {
    GenericType type;
    Generic(GenericType type) : type(type) {}
};

struct Integer : public Generic {
    int data;
    Integer(int data) : Generic(INTEGER), data(data) {}
};

struct Double : public Generic {
    double data;
    Double(double data) : Generic(DOUBLE), data(data) {}
};

struct String : public Generic {
    std::string data;
    String(std::string data) : Generic(STRING), data(data) {}
};

struct Bool : public Generic {
    bool data;
    Bool(bool data) : Generic(BOOL), data(data) {}
};

#endif

