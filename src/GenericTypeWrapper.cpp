#include <stdexcept>
#include "GenericTypeWrapper.h"
using namespace std;

Generic* Generic::wrapPrimitive(std::string data) {
    Generic* genericData;
    try {
        genericData = new Double(stod(data));
    } catch (invalid_argument ex) {
        genericData = new String(data);
    }
    return genericData;
}

GenericType Generic::type() const {
    return GENERIC;
}

bool operator ==(const Generic& left, const Generic& right) {
    if (left.type() != right.type()) {
        throw "DIFFERENT GENERIC TYPES CANNOT BE COMPARED";
    }
    GenericType type = left.type();
    if (type == DOUBLE) {
        return *((Double*)&left) == *((Double*)&right);
    } else if (type == STRING) {
        return *((String*)&left) == *((String*)&right);
    } else if (type == INTEGER) {
        return ((Integer*)&left)->data < ((Integer*)&right)->data;
    } else { //only BOOL types remaining
        return ((Bool*)&left)->data < ((Bool*)&right)->data;
    }
}

bool operator <(const Generic& left, const Generic& right) {
    if (left.type() != right.type()) {
        throw "DIFFERENT GENERIC TYPES CANNOT BE COMPARED";
    } else if (left.type() == BOOL) {
        throw "BOOLEANS CANNOT BE COMPARED";
    }
    GenericType type = left.type();
    if (type == DOUBLE) {
        return *((Double*)&left) < *((Double*)&right);
    } else if (type == STRING) {
        return *((String*)&left) < *((String*)&right);
    } else { //only INTEGER types remaining
        return ((Integer*)&left)->data < ((Integer*)&right)->data;
    }
}

bool operator >(const Generic& left, const Generic& right) {
    if (left.type() != right.type()) {
        throw "DIFFERENT GENERIC TYPES CANNOT BE COMPARED";
    } else if (left.type() == BOOL) {
        throw "BOOLEANS CANNOT BE COMPARED";
    }
    GenericType type = left.type();
    if (type == DOUBLE) {
        return ((Double*)&left)->data > ((Double*)&right)->data;
    } else if (type == STRING) {
        return ((String*)&left)->data > ((String*)&right)->data;
    } else { //only INTEGER types remaining
        return ((Integer*)&left)->data > ((Integer*)&right)->data;
    }
}

GenericType Integer::type() const {
    return INTEGER;
}

bool operator ==(const Integer& left, const Integer& right) {
    return left.data == right.data;
}

bool operator <(const Integer& left, const Integer& right) {
    return left.data < right.data;
}

bool operator >(const Integer& left, const Integer& right) {
    return left.data > right.data;
}

GenericType Double::type() const {
    return DOUBLE;
}

bool operator ==(const Double& left, const Double& right) {
    return left.data == right.data;
}

bool operator <(const Double& left, const Double& right) {
    return left.data < right.data;
}

bool operator >(const Double& left, const Double& right) {
    return left.data > right.data;
}

GenericType String::type() const {
    return STRING;
}

bool operator ==(const String& left, const String& right) {
    return left.data == right.data;
}

bool operator <(const String& left, const String& right) {
    return left.data < right.data;
}

bool operator >(const String& left, const String& right) {
    return left.data > right.data;
}

GenericType Bool::type() const {
    return BOOL;
}

bool operator ==(const Bool& left, const Bool& right) {
    return left.data == right.data;
}