#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H
#include "Array.h"

class SortedArray: public Array
{
    private:
        myPair* search (const string &, int begin, int end);
    public: 
        SortedArray();
        SortedArray(unsigned int sz);        
        ~SortedArray();
        bool insert(string &); 
        bool search (const string &, int &);
        bool erase(const string &);
};

#endif // SORTEDARRAY_H