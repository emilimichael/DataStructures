//
// Created by Έμιλη on 4/6/2021.
//

#include "BinarySearchTree.h"


BinarySearchTree::BinarySearchTree(){root = nullptr;}

BinarySearchTree::~BinarySearchTree(){ deleteTree(root);}


//Recursive function to insert words into BST
BinarySearchTree::Node* BinarySearchTree::Insert(std::string const& w, Node* n)
{
    //if root is null, create a new node and return it
    if (n == nullptr) {
        return new Node(w);
    }
    //if given word is less than the root node, recur for the left subtree
    if (w < n->word) {
        n->left = Insert(w, n->left);
    }
    //if given word is more than the root node, recur for the right subtree
    else if (w > n->word) {
        n->right = Insert(w, n->right);
    }
    //if given word already exists, increase occurrences.
    else if (w==n->word) {
        n->occurrences++;
    }
    return n;
}

//Iterating through the tree until we find the word starting from the root.
//@param found is to check if something went wrong or not.
BinarySearchTree::Node* BinarySearchTree::deleteNode(std::string const& w, Node* n)
{


    if ( n == nullptr){
        return nullptr;
    }

    else if (w < n->word){
        n->left = deleteNode(w, n->left);
    }
    else if (w > n->word){
        n->right = deleteNode(w, n->right);
    }
    else {
        //We found the word

        // Case 1: Node doesn't have a child (Leaf Node)
        if (n->left==nullptr && n->right==nullptr)
        {
            delete n;
            n = nullptr;
            return n;
        }
            //Case 2: Node has 1 child
        else if (n->left == nullptr){

            Node* temp = n;
            n = n -> right;
            delete temp;


            return n;
        }
        else if (n->right == nullptr){

            Node* temp = n;
            n=n->left;
            delete temp;


            return n;
        }

        // Node with 2 children. We find the inorder successor and replace n with it.

        Node* temp = minValue(n ->right);

        n->word = temp -> word;

        n -> right = deleteNode(temp->word, n->right);

    }



    return n;

}
//Searching the tree to see if the value exists. Iterate until we either find the word or if we reach null.
bool BinarySearchTree::Search(std::string  & w, int & o)
{
    Node* n = root;

    while(n) //while n is not NULL
    {
        if(w > n->word) {
            n = n->right;
        }
        else if(w < n->word) {
            n = n->left;
        }
        else //Word found
        {
            w = n->word;
            o = n->occurrences;
            return true;
        }
    }

    return false; //if something goes wrong or word not found
}

BinarySearchTree::Node* BinarySearchTree::minValue(Node* n)const{

    Node* current = n;

    //Loop down to find the left most leaf
    while (current && current->left != nullptr)
        current = current->left;

    return current;

}

//Printing tree in preorder
void BinarySearchTree::Preorder(Node* n) const
{
    if(n==nullptr)
        return;

    n->print();
    Preorder(n->left);
    Preorder(n->right);
}

//Printing tree in inorder
void BinarySearchTree::Inorder(Node* n)const
{
    if(n==nullptr)
        return;

    Inorder(n->left);
    n->print();
    Inorder(n->right);
}

//Printing tree in postorder
void BinarySearchTree::Postorder(Node* n)const
{
    if(n==nullptr)
        return;

    Postorder(n->left);
    Postorder(n->right);
    n->print();

}
/* This function traverses tree
in post order to delete each
and every node of the tree */
void BinarySearchTree::deleteTree(Node* n)
{
    if (n == nullptr) return;

    /* first delete both subtrees */
    deleteTree(n->left);
    deleteTree(n->right);


    delete n;
}
//size of Tree (total words)
int BinarySearchTree::getSize()
{
    int size = 0;
    getSize(root, size);
    return size;
}

void BinarySearchTree::getSize(Node *n, int & size)
{
    if (n == nullptr) return;
    size++;
    getSize(n->left, size);
    getSize(n->right, size);
}
//Get total word occurences
int BinarySearchTree::getOccurrences()
{
    int occurrences = 0;
    getOccurrences(root, occurrences);
    return occurrences;
}

void BinarySearchTree::getOccurrences(Node *n, int & occurrences)
{
    if (n == nullptr) return;
    occurrences += n->occurrences;
    getOccurrences(n->left, occurrences);
    getOccurrences(n->right, occurrences);
}

