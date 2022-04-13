/**
 * supplementary functions to open file and handle words
 **/

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
#include <string>
#include <sstream>
#include <regex>

using namespace std;

bool isWord(const string &word); // checks if is word, numbers are excluded and non - character chars. Regular expressions are used for the search
stringstream splitWord(string word, string delimeter); // splits a word
void clearWord(string &word); // clear and lowercase a word

#endif // MYFUNCTIONS_H