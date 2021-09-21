#ifndef _GENERICTYPEWRAPPER_H
#define _GENERICTYPEWRAPPER_H

#include <string>

enum GenericType {GENERIC, INTEGER, DOUBLE, STRING, BOOL};

struct Generic {
    virtual GenericType type() const;
    static Generic* wrapPrimitive(std::string data);
};
bool operator ==(const Generic& left, const Generic& right);
bool operator <(const Generic& left, const Generic& right);
bool operator >(const Generic& left, const Generic& right);

struct Integer : public Generic {
    int data;
    Integer(int data) : data(data) {}
    GenericType type() const;
};
bool operator ==(const Integer& left, const Integer& right);
bool operator <(const Integer& left, const Integer& right);
bool operator >(const Integer& left, const Integer& right);

struct Double : public Generic {
    double data;
    Double(double data) : data(data) {}
    GenericType type() const;
};
bool operator ==(const Double& left, const Double& right);
bool operator <(const Double& left, const Double& right);
bool operator >(const Double& left, const Double& right);

struct String : public Generic {
    std::string data;
    String(std::string data) : data(data) {}
    GenericType type() const;
};
bool operator ==(const String& left, const String& right);
bool operator <(const String& left, const String& right);
bool operator >(const String& left, const String& right);

struct Bool : public Generic {
    bool data;
    Bool(bool data) : data(data) {}
    GenericType type() const;
};
bool operator ==(const Bool& left, const Bool& right);

#endif

