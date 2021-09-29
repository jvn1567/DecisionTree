/**
 * @file GenericTypeWrapper.h
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief Wrapper classes for type string and the following primitives: double, 
 * integer, bool.
 * @version 0.1
 * @date 2021-09-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _GENERICTYPEWRAPPER_H
#define _GENERICTYPEWRAPPER_H

#include <string>
#include <vector>
#include <iostream>

enum GenericType {GENERIC, INTEGER, DOUBLE, STRING, BOOL};

static const std::vector<std::string> GenericTypeName = {
    "GENERIC", "INTEGER", "DOUBLE", "STRING", "BOOL"
};

/**
 * @brief Generic is used to capture type string and the following primitives: 
 * double, integer, bool. Once captured, it has methods to convert to the
 * appropriate type. Currently only getDouble() and getString() are implemented.
 * Generic is not instantiable and is used for polymorphic behaviors. Only 
 * sub-classes can be constructed.
 * 
 */
struct Generic {
    /**
     * @brief Returns the type the generic is storing.
     * 
     * @return enum STRING, DOUBLE, INTEGER, BOOL.
     */
    virtual GenericType type() const;
    /**
     * @brief Parses string data and subsequently constructs a sub-class 
     * instance on the heap of the parsed type (string, double, integer, bool).
     * 
     * @param data data, as a string, to be parsed.
     * @return Generic* 
     */
    static Generic* wrapPrimitive(std::string data);
    /**
     * @brief Get double from Generic.
     * 
     * @return double the double stored.
     * @throw invalid_argument if data cannot be converted to double.
     */
    double getDouble() const;
    /**
     * @brief Get string from Generic.
     * 
     * @return string the string stored.
     * @throw invalid_argument if data cannot be converted to string.
     */    
    std::string getString() const;
};

/**
 * @brief Compares two Generics for equality (==).
 * 
 * @param left 
 * @param right 
 * @return true equal.
 * @return false not equal.
 * @throw invalid_argument if the generics are not the same type, they cannot
 * be compared.
 */
bool operator ==(const Generic& left, const Generic& right);

/**
 * @brief Compares two Generics for less than (<).
 * 
 * @param left 
 * @param right 
 * @return true less than.
 * @return false not less than.
 * @throw invalid_argument if the generics are not the same type, they cannot
 * be compared.
 */
bool operator <(const Generic& left, const Generic& right);

/**
 * @brief Compares two Generics for greater than (>).
 * 
 * @param left 
 * @param right 
 * @return true greater than.
 * @return false not greater than.
 * @throw invalid_argument if the generics are not the same type, they cannot
 * be compared.
 */
bool operator >(const Generic& left, const Generic& right);

/**
 * @brief Compares two Generics for less than or equal to (<=).
 * 
 * @param left 
 * @param right 
 * @return true less than or equal to.
 * @return false not less than or equal to.
 * @throw invalid_argument if the generics are not the same type, they cannot
 * be compared.
 */
bool operator <=(const Generic& left, const Generic& right);

/**
 * @brief Compares two Generics for greater than or equal to (>=).
 * 
 * @param left 
 * @param right 
 * @return true greater than or equal to.
 * @return false not greater than or equal to.
 * @throw invalid_argument if the generics are not the same type, they cannot
 * be compared.
 */
bool operator >=(const Generic& left, const Generic& right);

/**
 * @brief Compares two Generics for inequality (!=).
 * 
 * @param left 
 * @param right 
 * @return true not equal.
 * @return false  equal.
 * @throw invalid_argument if the generics are not the same type, they cannot
 * be compared.
 */
bool operator !=(const Generic& left, const Generic& right);

/**
 * @brief Overrides the output (<<) operator.
 * 
 * @param out the output stream
 * @param generic the generic to output
 * @return ostream& the output stream
 */
std::ostream& operator <<(std::ostream& out, const Generic& generic);

/**
 * @brief Wrapper class for integer.
 * 
 */
struct Integer : public Generic {
    int data;
    /**
     * @brief Construct a new Integer object.
     * 
     * @param data 
     */
    Integer(int data) : data(data) {}
    /**
     * @brief Returns data type.
     * 
     * @return enum INTEGER.
     */
    GenericType type() const;
};
bool operator ==(const Integer& left, const Integer& right);
bool operator <(const Integer& left, const Integer& right);
bool operator >(const Integer& left, const Integer& right);
bool operator !=(const Integer& left, const Integer& right);
bool operator <=(const Integer& left, const Integer& right);
bool operator >=(const Integer& left, const Integer& right);
std::ostream& operator <<(std::ostream& out, const Integer& generic);

/**
 * @brief Wrapper class for double.
 * 
 */
struct Double : public Generic {
    double data;
    /**
     * @brief Construct a new Double object.
     * 
     * @param data 
     */
    Double(double data) : data(data) {}
    /**
     * @brief Returns data type.
     * 
     * @return enum DOUBLE.
     */
    GenericType type() const;
};
bool operator ==(const Double& left, const Double& right);
bool operator <(const Double& left, const Double& right);
bool operator >(const Double& left, const Double& right);
bool operator !=(const Double& left, const Double& right);
bool operator <=(const Double& left, const Double& right);
bool operator >=(const Double& left, const Double& right);
std::ostream& operator <<(std::ostream& out, const Double& generic);

/**
 * @brief Wrapper class for string.
 * 
 */
struct String : public Generic {
    std::string data;
    /**
     * @brief Construct a new String object.
     * 
     * @param data 
     */
    String(std::string data) : data(data) {}
    /**
     * @brief Returns data type.
     * 
     * @return enum STRING.
     */
    GenericType type() const;
};
bool operator ==(const String& left, const String& right);
bool operator <(const String& left, const String& right);
bool operator >(const String& left, const String& right);
bool operator !=(const String& left, const String& right);
bool operator <=(const String& left, const String& right);
bool operator >=(const String& left, const String& right);
std::ostream& operator <<(std::ostream& out, const String& generic);

/**
 * @brief Wrapper class for bool.
 * 
 */
struct Bool : public Generic {
    bool data;
    /**
     * @brief Construct a new Bool object.
     * 
     * @param data 
     */
    Bool(bool data) : data(data) {}
    /**
     * @brief Returns data type.
     * 
     * @return enum BOOL.
     */
    GenericType type() const;
};
bool operator ==(const Bool& left, const Bool& right);
bool operator !=(const Bool& left, const Bool& right);
std::ostream& operator <<(std::ostream& out, const Bool& generic);

#endif

