#include "HashTable.h"

HashTable::HashTable()
{
    size=10;
    elements=0;

    A = new myPair *[size]; // initialize empty data array
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}


HashTable::HashTable(int n)
{
    size=n;
    elements=0;

    A = new myPair*[size]; // initialize empty data array with size n
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}

HashTable::~HashTable()
{
    for (int i = 0; i < size; i++) // delete each pair element
        delete A[i];
    delete[] A;
    A=nullptr;
    elements=0;
    size=0;
}


unsigned int HashTable::hash(const string &word)
{
    unsigned long long key=0; // create a unique num for each string
    unsigned long long pow = 1;
    for (int i = 0; i < word.length(); i++){
        key += (unsigned long long)word[i]*pow;
        pow *= 26;
    }
    return key%size;
}

unsigned int HashTable::hash2(unsigned int d)
{
    return (d+1)%size; // assign or search position in Array
}

bool HashTable::insert (const string &word)
{
    myPair * pair = search(word); 

    if (pair!=nullptr){
        // check if word already in, if in just add 1 to the previous value
        pair->occurences += 1;
        return false;
    }

    elements++;
    
    if (elements>=size/2)
    {
        // resize if elements exceed 50% of the array size
        myPair **temp;
        size *= 2;
        temp = new myPair*[size];
        for(int i=0;i<size;i++)
            temp[i]=nullptr;

        for (int i=0;i<size/2;i++)
        {
            if (A[i]!=nullptr)
            {
                unsigned int p = hash(A[i]->word);
                while (temp[p]!=nullptr)
                    p = hash2(p);
                temp[p]=A[i];
                A[i]=nullptr;
            }        
        }
        delete[]A;
        A=temp;
    }
    
    unsigned int p = hash(word); // assign the word - occurences pair to the HashTable

    while (A[p]!=nullptr)
        p = hash2(p);
    A[p]=new  myPair(word,1);
    return true;
}


myPair * HashTable::search(const string &word)
{
    unsigned int p = hash(word); // find the position at the array of the word - occurences pair
    while (A[p]!=nullptr && A[p]->word!=word){ // search the Array till the word is found or until a nullpoiner is found 
        p = hash2(p);
    }
    return A[p];
}

bool HashTable::search(const string &word, int &occurences)
{
    myPair *p = search(word);

    if (p==nullptr){ // if a nullpointer is found means that the word searched has NOT been found so the return value is false
        occurences = 0;
        return false;
    }

    occurences = p->occurences; // else pair occurences are assigned to reference variable data 
    return true;
}

unsigned int HashTable::getSize(){return size;}

unsigned int HashTable::getElements(){return elements;}

unsigned int HashTable::getOccurrences()
{
    unsigned int occurrences = 0;
    for (int i = 0; i < size; i++){
        if (A[i] != nullptr)
            occurrences += A[i]->occurences;
    }
    return occurrences;
}

void HashTable::print()
{
    for (int i = 0; i < size; i++){
        if (A[i] != nullptr)
            cout<<A[i]->word<<" : "<<A[i]->occurences<<endl;
    }
}