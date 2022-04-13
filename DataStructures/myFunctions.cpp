#include "myFunctions.h"

bool isWord(const string &word)
{
    regex m (".*[a-zA-Z].*");  
    if (!regex_match(word, m))
        return false;

    return true;
}

stringstream splitWord(string word, string delimeter)
{
    int start = 0;
    int end = word.find(delimeter);
    stringstream words;

    while (end != -1) {
        words << word.substr(start, end - start) << " ";
        start = end + delimeter.size();
        end = word.find(delimeter, start);
    }

    return words;
}

void clearWord(string &word)
{

    stringstream result;
    const regex removals ("[^a-zA-Z]");
    regex_replace(ostream_iterator<char>(result), word.begin(), word.end(), removals, "");

    word = result.str();  
    for_each(word.begin(), word.end(), [](char & c){
        c = ::tolower(c);
    });
    
}