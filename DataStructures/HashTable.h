#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "myPair.h"
#include <iostream>

class HashTable
{
    private:
        unsigned int size;
        unsigned int elements;
        myPair* *A;
        unsigned int hash(const string &);
        unsigned int hash2(unsigned int);
        myPair* search(const string &);
    public:
        HashTable();
        HashTable(int n);
        ~HashTable();
        bool insert(const string &);
        bool search(const string &, int &);
        unsigned int getSize(); // returns the size of the array
        unsigned int getElements(); // returns the words stored
        unsigned int getOccurrences(); // returns the occurences stored
        void print(); 
};


#endif // HASHTABLE_H