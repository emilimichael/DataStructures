#include "Array.h"

Array::Array()
{
    size = 10;
    A = new myPair *[size];
    for (int i = 0; i < size; i++)
        A[i] = nullptr;
    elements = 0;
    searchPos = 0;
}

Array::Array(unsigned int sz)
{
    size = sz;
    A = new myPair*[size];
    for (int i = 0; i < size; i++)
        A[i] = nullptr;
    elements = 0;
    searchPos = 0;
}

Array::~Array()
{
    for (int i = 0; i < size; i++)
        delete A[i];
    delete [] A;
    A = nullptr;
    size = 0;
    elements = 0;
    searchPos = 0;
}

bool Array::insert(string & word)
{
    myPair * pair = search(word); 
    if (pair!=nullptr){
        // check if word already in, if in just add 1 to the previous value
        pair->occurences += 1;
        return false;
    }
    
    A[elements] = new myPair(word,1);
    elements++;

    if (elements >= size/2){ 
        // resize the Array if elements are >= size/2
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

myPair * Array::search(const string &word)
{
    // this method is used only by the class
    myPair * temp = nullptr;

    for (int i = 0; i < elements; i ++){
        if (A[i]->word == word){
            temp = A[i];
            searchPos = i;
            return temp;
        }
    }

    return temp;
}

bool Array::search(const string &word, int & occurences)
{
    if (elements == 0){
        occurences = 0;
        return false;
    }

    myPair * temp = search(word);

    if (temp == nullptr){
        occurences = 0;
        return false;
    }
    
    occurences = temp->occurences;

    return true;
}

bool Array::erase(const string &word)
{
    if (elements == 0)
        return false;
    
    if (search(word) == nullptr)
        return false;

    delete A[searchPos];
    A[searchPos] = nullptr;

    for (int i = searchPos+1; i <= elements; i++) // move the elements
        A[i-1] = A[i];
    
    elements--;

    if (elements < size/4){ 
        //resize if elements are less that size/4
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

unsigned int Array::getSize(){return size;}

unsigned int Array::getElements(){return elements;}

unsigned int Array::getOccurrences()
{
    int occurrences = 0;
    for (int i = 0; i < elements; i++)
        occurrences += A[i]->occurences;
    return occurrences;
}

void Array::print()
{
    for (int i = 0; i < elements; i++)
        cout<<A[i]->word<<" "<<A[i]->occurences<<endl;
}

string Array::get(int pos)
{
    if (elements == 0) throw runtime_error("Empty Array to use get method");
    if (pos < -1) throw runtime_error("Position argument cant be negative to get method");
    if (pos >= elements) throw runtime_error("Position argument exceeds existing cells");
    return A[pos]->word;
}