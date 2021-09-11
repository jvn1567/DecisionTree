#ifndef _GENERICTYPEWRAPPER_H
#define _GENERICTYPEWRAPPER_H

#include <string>

enum GenericType {GENERIC, INTEGER, DOUBLE, STRING, BOOL};

struct Generic {
    virtual GenericType type() {
        return GENERIC;
    }
};

struct Integer : public Generic {
    int data;
    Integer(int data) : data(data) {}
    GenericType type() {
        return INTEGER;
    }
};

struct Double : public Generic {
    double data;
    Double(double data) : data(data) {}
    GenericType type() {
        return DOUBLE;
    }
};

struct String : public Generic {
    std::string data;
    String(std::string data) : data(data) {}
    GenericType type() {
        return STRING;
    }
};

struct Bool : public Generic {
    bool data;
    Bool(bool data) : data(data) {}
    GenericType type() {
        return BOOL;
    }
};

#endif

