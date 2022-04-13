//
// Created by Έμιλη on 4/6/2021.
//

#include "AVLtree.h"
AVLtree::AVLtree() = default;

AVLtree::~AVLtree() = default;

//function to right rotate subtree nodeed with y

AVLtree::Node* AVLtree::rightRotate(Node* &y)
{
    Node* x = y->left;
    y->left = x->right;

    // Perform rotation
    x->right = y;


    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new node
    return x;
}

// left rotate the sub tree nodeed with x
AVLtree::Node* AVLtree::leftRotate(Node* &x)
{
    Node* y = x->right;
    x->right = y->left;  //tree two

    // Perform rotation
    y->left = x;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new node
    return y;
}

int AVLtree::height(Node* n) const{

    if (n == nullptr){
        return 0;
    }
    return n->height;
}


AVLtree::Node* AVLtree:: leftRightRotate(Node* &n){

    n->left = leftRotate(n->left);

    return rightRotate( n);

}

AVLtree::Node* AVLtree::rightLeftRotate(Node* &n){

    n->right = rightRotate(n->right);

    return leftRotate(n);

}


    int AVLtree::getBalance(Node* n){


    return height(n->left) - height(n->right);


}


AVLtree::Node* AVLtree::Insert(std::string const &w, Node* n){

    //if node is null, create a new node and return it
    if (n == nullptr) {
        return new Node(w);
    }
    //if given word is less than the node node, recur for the left subtree
    if (w < n->word) {
        n->left = Insert(w, n->left);
    }
        //if given word is more than the node node, recur for the right subtree
    else if (w > n->word) {
        n->right = Insert(w, n->right);
    }
        //if given word already exists, increase occurrences.
    else if (w==n->word){
        n->occurrences++;
        return n;
    }


    //Update the height of n.

    n->height = 1 + max(height(n->left),  height(n->right));

    int balance = getBalance(n);


    // rotate if unbalanced

    // Left Left Case
    if (balance > 1 && w < n->left->word)
        return rightRotate(n);

    // Right Right Case
    if (balance < -1 && w > n->right->word)
        return leftRotate(n);

    // Left Right Case

    if (balance > 1 && w > n->left->word)
    {

        return leftRightRotate(n);
    }

    // Right Left Case
    if (balance < -1 && w< n->right->word)
    {
        return rightLeftRotate(n);
    }
    
    return n;
}


AVLtree::Node* AVLtree::deleteNode(std::string const& w,  Node* node)
{

    if (node == nullptr){
        return nullptr;
    }

    else if (w < node->word){
        node->left = deleteNode(w,node->left );
    }
    else if (w >node->word){
        node->right = deleteNode( w, node->right);
    }
    else {
        //We found the word

        // Case 1: Node doesn't have a child (Leaf Node)
        if (node->left==nullptr && node->right==nullptr)
        {
            delete node;
            node = nullptr;
        }
            //Case 2: Node has 1 child
        else if (node->left == nullptr){

            Node* temp = node;
            node = node ->right;
            delete temp;


        }
        else if (node->right == nullptr){

            Node* temp = node;
            node = node->left;
            delete temp;


        }

        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValue(node->right);

            // Copy the inorder successor's
            // data to this node
            node->word = temp->word;

            // Delete the inorder successor
            node->right = deleteNode(temp->word, node->right
            );
        }
    }

    // If the tree had only one node
    // then return
    if (node == nullptr){
        return node;
    }

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(node);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case (single right rotation)
    if (balance > 1 &&
        getBalance(node->left) >= 0)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 &&
        getBalance(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case (single left rotation)
    if (balance < -1 &&
        getBalance(node->right) <= 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 &&
        getBalance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}



