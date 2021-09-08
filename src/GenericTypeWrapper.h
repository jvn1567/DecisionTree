#ifndef _GenericTypeWrapper_h
#define _GenericTypeWrapper_h

#include <string>

struct Generic {};

struct Integer : public Generic {
    int data;

    Integer(int data) {
        this->data = data;
    }
};

struct Double : public Generic {
    double data;
    
    Double(double data) {
        this->data = data;
    }
};

struct String : public Generic {
    std::string data;
    
    String(std::string data) {
        this->data = data;
    }
};

struct Bool : public Generic {
    bool data;
    
    Bool(bool data) {
        this->data = data;
    }
};

#endif

