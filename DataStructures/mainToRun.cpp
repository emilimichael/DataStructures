/**
 * The main file that implements all the structures and functions made
 **/

#include "HashTable.h"
#include "AVLtree.h"
#include "BinarySearchTree.h"
#include "Array.h"
#include "SortedArray.h"
#include "myFunctions.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>  
#include <chrono>
#define Q_LENGTH 1000

/**
 * The 1st argument passed is the file
 **/

int main (int argc, char** argv)
{
    auto startProgram = chrono::high_resolution_clock::now();

    ifstream ifs; 
    ifs.open(argv[1]); // 1st argument is the file path

    if (!ifs.is_open()) throw runtime_error("file not found!");


    string word;
    stringstream words;
    // initiate structures
    AVLtree avlTree = AVLtree();
    BinarySearchTree tree = BinarySearchTree();
    Array arr = Array();
    SortedArray sortArr = SortedArray();
    HashTable ht = HashTable();

    // insert words in each structure
    while (ifs>>word){

        if (!isWord(word))
            continue;
        
        if (word.find("--") != string::npos){ // split words seperated by --
            words = splitWord(word, "--");
            while (words>>word){
                if (isWord(word)){
                    clearWord(word);
                    avlTree.Insert(word);
                    tree.Insert(word);
                    arr.insert(word);
                    sortArr.insert(word);
                    ht.insert(word);
                } 
            }
        }
        else{
            clearWord(word);
            avlTree.Insert(word);
            tree.Insert(word);
            arr.insert(word);
            sortArr.insert(word);
            ht.insert(word);
        }
        
    }

    ifs.close();

    // create Q set
    string *Q = new string[Q_LENGTH];
    srand((unsigned) time(0));
    int randomNumber;
    for (int i = 0; i < Q_LENGTH; i++){
        randomNumber = (rand() % arr.getElements());
        Q[i] = arr.get(randomNumber);
    }

    int instances; 
    // Record search time Array
    cout<<"------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"ARRAY"<<endl;
    auto startArray = chrono::high_resolution_clock::now();
    for (int i = 0; i < Q_LENGTH; i++){
        arr.search(Q[i], instances);
        cout<<Q[i]<<" : "<<instances<<", ";
    }
    auto finishArray = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedArray = finishArray - startArray;
    cout<<endl;

    // Record search time SortedArray
    cout<<"------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"SORTEDARRAY"<<endl;
    auto startSortedArray = chrono::high_resolution_clock::now();
    for (int i = 0; i < Q_LENGTH; i++){
        sortArr.search(Q[i], instances);
        cout<<Q[i]<<" : "<<instances<<", ";
    }
    auto finishSortedArray = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedSortedArray = finishSortedArray - startSortedArray;
    cout<<endl;

    // Record search time HashTable
    cout<<"------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"HASHTABLE"<<endl;
    auto startHashTable = chrono::high_resolution_clock::now();
    for (int i = 0; i < Q_LENGTH; i++){
        ht.search(Q[i], instances);
        cout<<Q[i]<<" : "<<instances<<", ";
    }
    auto finishHashTable = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedHashTable = finishHashTable - startHashTable;
    cout<<endl;

    // Record search time BinarySearchTree
    cout<<"------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"BST"<<endl;
    auto startBST = chrono::high_resolution_clock::now();
    for (int i = 0; i < Q_LENGTH; i++){
        tree.Search(Q[i], instances);
        cout<<Q[i]<<" : "<<instances<<", ";
    }
    auto finishBST = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedBST = finishBST - startBST;
    cout<<endl;

    // Record search time AVLtree
    cout<<"------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"AVL"<<endl;
    auto startAVL = chrono::high_resolution_clock::now();
    for (int i = 0; i < Q_LENGTH; i++){
        avlTree.Search(Q[i], instances);
        cout<<Q[i]<<" : "<<instances<<", ";
    }
    auto finishAVL = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedAVL = finishAVL - startAVL;
    cout<<endl;

    // Report results
    cout<<"------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    auto finishProgram = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedProgram = finishProgram - startProgram;

    cout<<"Array search time "<<elapsedArray.count()<<" s"<<" Words "<<arr.getElements()<<" Occurences "<<arr.getOccurrences()<<endl;
    cout<<"SortedArray search time "<<elapsedSortedArray.count()<<" s"<<" Words "<<sortArr.getElements()<<" Occurences "<<sortArr.getOccurrences()<<endl;
    cout<<"HashTable search time "<<elapsedHashTable.count()<<" s"<<" Words "<<ht.getElements()<<" Occurences "<<ht.getOccurrences()<<endl;
    cout<<"BinarySearchTree search time "<<elapsedBST.count()<<" s"<<" Words "<<tree.getSize()<<" Occurences "<<tree.getOccurrences()<<endl;
    cout<<"AVLtree search time "<<elapsedAVL.count()<<" s"<<" Words "<<avlTree.getSize()<<" Occurences "<<avlTree.getOccurrences()<<endl;
    cout<<"Total program time "<<elapsedProgram.count()<<" s"<<endl;

    return 0;
}