#include <stdexcept>
#include "GenericTypeWrapper.h"
using namespace std;

Generic* Generic::wrapPrimitive(std::string data) {
    Generic* genericData;
    try {
        genericData = new Double(stod(data));
    } catch (invalid_argument) {
        genericData = new String(data);
    }
    return genericData;
}

GenericType Generic::type() const {
    return GENERIC;
}

GenericType Integer::type() const {
    return INTEGER;
}

GenericType Double::type() const {
    return DOUBLE;
}

GenericType String::type() const {
    return STRING;
}

GenericType Bool::type() const {
    return BOOL;
}