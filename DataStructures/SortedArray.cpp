#include "SortedArray.h"

SortedArray::SortedArray() = default; // the parent class constructor is called

SortedArray::SortedArray(unsigned int sz):Array(sz){}; // the parent class constructor is called

SortedArray::~SortedArray() = default; // the parent class destructor is called

bool SortedArray::insert(string & word)
{
    // when elements are inserted they a binary search is used to find the position 
    // for them to be stored. The binary search is done in the search(string, int, int) method

    if (elements == 0){
        elements++;
        A[0] = new myPair(word,1);
        return true;
    }
    
    myPair * pair = nullptr;

    if (word < A[0]->word)
        searchPos = 0; // if to be inserted in the 1st position
    else if (word > A[elements-1]->word)
        searchPos = elements-1; // if to be inserted in the last position
    else{
        // check if word already in, if in just add 1 to the previous value
        pair = search(word, 0, elements -1); 
        if (pair!=nullptr){
            pair->occurences += 1;
            return false;    
        }   
    }

    if (A[searchPos]->word < word)
        searchPos +=1;

    for (int i = elements; i > searchPos; i--) // the array is swaped for the new value to be inserted
        A[i] = A[i-1];

    A[searchPos] = new myPair(word,1);
    elements ++;

    if (elements >= size/2){ // resize the Array if elements are >= size/2
        myPair ** temp;
        size*=2;
        temp = new myPair*[size];
        for (int i = 0; i < size; i++)
            temp[i] = nullptr;
        for (int i = 0; i < elements; i++)
            temp[i] = A[i];
        delete[] A;
        A = temp;
    }

    return true;
}

myPair* SortedArray::search (const string & word, int begin, int end)
{
    // a recurcive binary search implementation
    if (begin == end){
        searchPos = begin;
        if (A[begin]->word == word)
            return A[begin];
        else
            return nullptr;
    }

    int mid = (end+begin)/2;

    if (A[mid]->word == word){        
        searchPos = mid;
        return A[mid];
    }
    else if (A[mid]->word > word){
        if (mid == begin){
            searchPos = mid;
            return nullptr;
        }
        return search(word, begin, mid - 1);
    }
    else{
        return search(word, mid + 1, end);
    }
}

bool SortedArray::search (const string & word, int & occurences)
{
    if (elements == 0) // case no words in array
        return false;
    
    if (word < A[0]->word || word > A[elements-1]->word) // checks if the word searched is out of bounds
        return false;

    myPair * temp = search(word, 0, elements-1);
    
    if (temp == nullptr)
        return false;
    
    occurences = temp->occurences;
    return true;

}

bool SortedArray::erase(const string & word)
{
    if (elements == 0) // case no words
        return false;
    
    if (word < A[0]->word || word > A[elements-1]->word) // case out of bounds
        return false;
    
    if (search(word, 0, elements - 1) == nullptr) // case not found
        return false;

    delete A[searchPos];
    A[searchPos] = nullptr;

    for (int i = searchPos+1; i <= elements; i++) // swift the array
        A[i-1] = A[i];
    
    elements--;

    if (elements < size/4){ //resize if elements are less that size/4
        myPair **temp;
        size /= 2;
        temp = new myPair*[size];

        for(int i=0;i<size;i++)
            temp[i]=A[i];

        delete[]A;
        A=temp;
    }

    return true;
}