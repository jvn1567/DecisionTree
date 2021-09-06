// Utility functions
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "lib132.h"

using namespace std;

/* Lower cases a string using recursion. Assumes that the string is not NULL.

    Params:
        s (string, reference)
    Returns (string): A lower case string. */
string toLowerCase(string s) {
    // Base case: if there are no letters left, 
    // return an empty string
    if (s.length() == 0) {
        return "";
    } else {
        // Seperate the first character from the rest 
        char letter = s[0];
        string rest = s.substr(1);
        letter = tolower(letter);
        // convert the first character to lowercase and call
        // the function on the rest
        return letter + toLowerCase(rest);
    }
}

/* Determines equality of two strings (case insensitive). Assumes that neither string is NULL.

    Params:
        s1 (string, value)
        s2 (string, value)
    Returns (bool) */
bool equalsIgnoreCase(string s1, string s2) {
    return toLowerCase(s1) == toLowerCase(s2);
}

/* Counts the number of word tokens separated by whitespace. Assumes the string is not NULL.

    Params:
        line (string, value)
    Returns (int). */
int countWords(string line) {
    istringstream lineInput(line.c_str());
    string word;
    int count = 0;
    while (lineInput >> word) {
        count++;
    }
    return count;
}

/* Determines if a character is a vowel. Assumes the character is not NULL.

    Params:
        c (character, value)
    Returns (bool) */
bool isVowel(char c) {
    string vowels = "aeiou";
    return vowels.find(c) != string::npos;
}

bool equalsPrefix(string prefix, string s) {
    if (prefix.length() == 0) {
        return true;
    } else if (tolower(prefix[0]) != tolower(s[0])) {
        return false;
    } else {
        return equalsPrefix(prefix.substr(1), s.substr(1));
    }
}

ifstream openFile(string fileName) {
    ifstream input(fileName);
    while (!input.good()) {
        cout << "File not found. Try again: ";
        getline(cin, fileName);
        input.open(fileName);
    }
    return input;
}