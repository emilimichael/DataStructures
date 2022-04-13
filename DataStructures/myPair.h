#ifndef MYPAIR_H
#define MYPAIR_H
#include <string>

using namespace std;

class myPair
{
    public:
        myPair(string w, int occ)
        {
            word=w;
            occurences=occ;
        }
        string word;
        int occurences;
};

#endif // MYPAIR_H