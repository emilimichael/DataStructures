//
// Created by Έμιλη on 4/6/2021.
//

#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H
#include "BinarySearchTree.h"


class AVLtree : public BinarySearchTree
{
public:
    /** Default constructor */
    AVLtree();
    /** Default destructor */
    ~AVLtree();

    void Insert(std::string const& w) override {root = Insert(w, root);}
    void deleteNode(std::string const& w) override { root =deleteNode(w, root);}

    int getBalance(Node* n) ;


private:

    Node* rightRotate(Node* &n);
    Node* leftRotate(Node* &n);
    Node* leftRightRotate(Node* &n);
    Node* rightLeftRotate(Node* &n);

    int max(int a, int b){return (a>b)? a : b;} //function to be used for height comparison
    int  height(Node *n) const;

    Node* Insert(std::string const& w, Node* n) override;
    Node* deleteNode (std::string const& w, Node* n) override;
};


#endif //DATASTRUCTURES_AVLTREE_H