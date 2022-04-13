//
// Created by Έμιλη on 4/6/2021.
//

#ifndef DATASTRUCTURES_BINARYSEARCHTREE_H
#define DATASTRUCTURES_BINARYSEARCHTREE_H
#include <string>
#include <iostream>


class BinarySearchTree
{
public:



    BinarySearchTree();
    ~BinarySearchTree();

    virtual void Insert (std::string const& w) { root = Insert(w,root);}
    bool Search (std::string & w, int & o);

    virtual void deleteNode(std::string const& w){ root =deleteNode(w, root);}

    void Preorder ()const {Preorder(root);}
    void Inorder ()const {Inorder(root);}
    void Postorder ()const {Postorder(root);}
    int getSize();
    int getOccurrences();



protected:

    class Node {

    public:

        Node(std::string word) {this->word = word; occurrences = 1; right = left = nullptr; height = 1;}
        int occurrences;
        std::string word;
        Node* left;
        Node* right;
        int height; //for the AVL tree

        void print() {std::cout<<"Word:  "<<word<<" Occurrences: "<<occurrences<<" ";}

    };


    Node* root;
    Node* minValue (Node* n)const;

    virtual Node* Insert(std::string const& w, Node* n);
    void Preorder (Node*)const;
    void Inorder (Node*)const;
    void Postorder (Node*) const;

    virtual Node* deleteNode(std::string const& w, Node* n);
    void deleteTree(Node* n);
    void getSize (Node *, int &);
    void getOccurrences (Node *, int &);




};



#endif //DATASTRUCTURES_BINARYSEARCHTREE_H
