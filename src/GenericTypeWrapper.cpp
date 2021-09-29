/**
 * @file GenericTypeWrapper.cpp
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief Implementation of GenericTypeWrapper.h.
 * @version 0.1
 * @date 2021-09-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "GenericTypeWrapper.h"
#include <stdexcept>
using namespace std;

#include <iostream>

//GENERIC

Generic* Generic::wrapPrimitive(std::string data) {
    Generic* genericData;
    try {
        genericData = new Double(stod(data));
    } catch (invalid_argument& ex) {
        genericData = new String(data);
    }
    return genericData;
}

GenericType Generic::type() const {
    return GENERIC;
}

double Generic::getDouble() const {
    if (type() != DOUBLE) {
        throw invalid_argument(GenericTypeName[type()] + " CANNOT BE EXTRACTED AS DOUBLE");
    }
    return ((Double*)this)->data;
}

string Generic::getString() const {
    if (type() != STRING) {
        throw invalid_argument(GenericTypeName[type()] + " CANNOT BE EXTRACTED AS STRING");
    }
    return ((String*)this)->data;
}

bool operator ==(const Generic& left, const Generic& right) {
    if (left.type() != right.type()) {
        throw invalid_argument("DIFFERENT GENERIC TYPES CANNOT BE COMPARED");
    }
    GenericType type = left.type();
    if (type == DOUBLE) {
        return *((Double*)&left) == *((Double*)&right);
    } else if (type == STRING) {
        return *((String*)&left) == *((String*)&right);
    } else if (type == INTEGER) {
        return *((Integer*)&left) < *((Integer*)&right);
    } else { //only BOOL types remaining
        return *((Bool*)&left) < *((Bool*)&right);
    }
}

bool operator <(const Generic& left, const Generic& right) {
    if (left.type() != right.type()) {
        throw invalid_argument("DIFFERENT GENERIC TYPES CANNOT BE COMPARED");
    } else if (left.type() == BOOL) {
        throw invalid_argument("BOOLEANS CANNOT BE COMPARED");
    }
    GenericType type = left.type();
    if (type == DOUBLE) {
        return *((Double*)&left) < *((Double*)&right);
    } else if (type == STRING) {
        return *((String*)&left) < *((String*)&right);
    } else { //only INTEGER types remaining
        return *((Integer*)&left) < *((Integer*)&right);
    }
}

bool operator >(const Generic& left, const Generic& right) {
    if (left.type() != right.type()) {
        throw invalid_argument("DIFFERENT GENERIC TYPES CANNOT BE COMPARED");
    } else if (left.type() == BOOL) {
        throw invalid_argument("BOOLEANS CANNOT BE COMPARED");
    }
    GenericType type = left.type();
    if (type == DOUBLE) {
        return *((Double*)&left) > *((Double*)&right);
    } else if (type == STRING) {
        return *((String*)&left) > *((String*)&right);
    } else { //only INTEGER types remaining
        return *((Integer*)&left) > *((Integer*)&right);
    }
}

bool operator <=(const Generic& left, const Generic& right) {
    return left < right || left == right;
}

bool operator >=(const Generic& left, const Generic& right) {
    return left > right || left == right;
}

bool operator !=(const Generic& left, const Generic& right) {
    return !(left == right);
}

ostream& operator <<(ostream& out, const Generic& generic) {
    GenericType type = generic.type();
    if (type == DOUBLE) {
        out << generic.getDouble();
    } else if (type == STRING) {
        out << generic.getString();
    } else {
        //unimplemented other types
    }
    return out;
}

//INTEGER

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

bool operator !=(const Integer& left, const Integer& right) {
    return left.data != right.data;
}

bool operator <=(const Integer& left, const Integer& right) {
    return left.data <= right.data;
}

bool operator >=(const Integer& left, const Integer& right) {
    return left.data >= right.data;
}

ostream& operator <<(ostream& out, const Integer& integer) {
    out << integer.data;
    return out;
}

//DOUBLE

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

bool operator !=(const Double& left, const Double& right) {
    return left.data != right.data;
}

bool operator <=(const Double& left, const Double& right) {
    return left.data <= right.data;
}

bool operator >=(const Double& left, const Double& right) {
    return left.data >= right.data;
}

ostream& operator <<(ostream& out, const Double& doub) {
    out << doub.data;
    return out;
}

//STRING

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

bool operator !=(const String& left, const String& right) {
    return left.data != right.data;
}

bool operator <=(const String& left, const String& right) {
    return left.data <= right.data;
}

bool operator >=(const String& left, const String& right) {
    return left.data >= right.data;
}

ostream& operator <<(ostream& out, const String& str) {
    out << str.data;
    return out;
}

//BOOL

GenericType Bool::type() const {
    return BOOL;
}

bool operator ==(const Bool& left, const Bool& right) {
    return left.data == right.data;
}

bool operator !=(const Bool& left, const Bool& right) {
    return left.data != right.data;
}

ostream& operator <<(ostream& out, const Bool& boolean) {
    out << boolean.data;
    return out;
}