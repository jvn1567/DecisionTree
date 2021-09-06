#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string toLowerCase(string s);
bool equalsIgnoreCase(string s1, string s2);
int countWords(string line);
bool isVowel(char c);
bool equalsPrefix(string prefix, string s);
ifstream openFile(string fileName);