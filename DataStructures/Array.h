#ifndef ARRAY_H
#define ARRAY_H
#include "myPair.h"
#include <iostream>

class Array // this class will be inhereted by the SortedArray Class
{   
    private:
        myPair* search (const string &); // this method will be overriden in SortedArray Class, but with different args
    protected:
        myPair* *A;
        unsigned int size;
        unsigned int elements;
        unsigned int searchPos; // for SortedArray
    public: 
        Array();
        Array(unsigned int);
        ~Array();
        virtual bool insert(string &);
        virtual bool search(const string &, int &);
        virtual bool erase(const string &);
        unsigned int getSize(); // returns the size of the array
        unsigned int getElements(); // returns the words stored
        unsigned int getOccurrences(); // returns the occurrences stored
        void print();
        string get(int); // this method return the element that is in the int position passed as argument

};

#endif // ARRAY_H