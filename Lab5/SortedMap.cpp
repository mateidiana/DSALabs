#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <utility>
#include <vector>
using namespace std;

//worst=best=average=θ(1)
SortedMap::SortedMap(Relation r) {
    rel=r;
    root= nullptr;
    nrElems=0;
}

//worst=θ(n)
//best=θ(1)
//average=θ(log n)
TValue SortedMap::add(TKey k, TValue v) {
    //If tree is empty, add root
    if (root== nullptr)
    {
        Node *newNode=new Node;
        newNode->info= make_pair(k,v);
        newNode->left= nullptr;
        newNode->right= nullptr;
        root=newNode;
        nrElems++;
        return NULL_TVALUE;
    }

    //Initialise current node based on relation and a previous node
    Node* current = root;
    Node* prevNode = root;
    if(rel(k, current->info.first) && current->info.first != k){
        current = current->left;
    }
    else{
        if(current->info.first != k) {
            current = current->right;
        }
    }

    //Traverse tree based on relation until either identical key is found or we arrive at a leaf
    while(current != nullptr){
        if(prevNode->info.first == k){
            break;
        }
        if(rel(k, current->info.first))
        {
            prevNode = current;
            current = current->left;
        }
        else{
            prevNode = current;
            current = current->right;
        }

    }

    //If key already exists, only update the value and return the old data
    if(prevNode->info.first == k){
        TValue t = prevNode->info.second;
        prevNode->info.second = v;
        return t;
    }

    //Make a new node, add as leaf
    Node* newNode = new Node;
    newNode->info = make_pair(k, v);
    newNode->left = nullptr;
    newNode->right = nullptr;
    if(rel(k, prevNode->info.first)){
        prevNode->left = newNode;
    }
    else{
        prevNode->right = newNode;
    }
    nrElems++;

    return NULL_TVALUE;
}

//worst=θ(n)
//best=θ(1)
//average=θ(log n)
TValue SortedMap::search(TKey k) const {
    Node *current=root;
    while (current!= nullptr)
    {
        if(current->info.first == k){
            return current->info.second;
        }
        if(rel(k, current->info.first)){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    return NULL_TVALUE;
}

//worst=θ(n)
//best=θ(1)
//average=θ(log n)
TValue SortedMap::remove(TKey k) {
    //Find node that needs to be removed based on relation
    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr && current->info.first != k) {
        parent = current;
        if (rel(k, current->info.first)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    //Return null if searched node doesn't exist
    if (current == nullptr) {
        return NULL_TVALUE;
    }

    TValue removedValue = current->info.second;

    //Delete node if searched node is root and only root is left
    //Delete node if node is leaf
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            root = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    }

        //If searched node has only one child replace node with child
    else if (current->left == nullptr || current->right == nullptr) {
        Node* child;
        if (current->left != nullptr) {
            child = current->left;
        } else {
            child = current->right;
        }
        if (current == root) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;

        //Find node with the lowest value from the right subtree
        //Replace value of searched node with min from right
        //Now min needs to be deleted, function is called again
    } else {
        TElem minElem = findMin(current->right);
        TKey minKey = minElem.first;
        TValue minValue = minElem.second;
        current->info = minElem;
        remove(minKey);
        current->info.second = minValue;
    }

    nrElems--;
    return removedValue;
}

//worst=best=average=θ(1)
int SortedMap::size() const {
    return nrElems;
}

//worst=best=average=θ(1)
bool SortedMap::isEmpty() const {
    return (nrElems==0);
}

//worst=best=average=θ(1)
SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

//worst=θ(n)
//best=θ(log n)
//average=θ(log n)
TElem SortedMap::findMin(Node *startRoot) {
    if(startRoot == nullptr){
        return NULL_TPAIR;
    }

    Node* current = startRoot;
    while(current->left != nullptr){
        current = current->left;
    }
    return current->info;
}

//worst=average=θ(n*m)
//best=θ(1)

//pre this and other are maps
//post true if this is equal to other
//     false otherwise
bool SortedMap::operator==(const SortedMap &other) const{
    if (nrElems!=other.nrElems)
        return false;

    //traverse other in level order and store all elements in array elems
    int i=0;
    int j=0;
    Node **queue=new Node*[100];
    Node **elems=new Node *[100];

    Node *curr=other.root;
    if (curr!= nullptr)
    {
        elems[i]=curr;
        i++;
    }

    if (curr->left!= nullptr)
    {
        queue[j]=curr->left;
        j++;
    }

    if (curr->right!= nullptr)
    {
        queue[j]=curr->right;
        j++;
    }

    while (j>0)
    {
        curr=queue[0];
        elems[i++]=curr;
        for (int k=1;k<j;k++)
        {
            queue[k-1]=queue[k];
        }
        j--;
        if (curr->left!= nullptr)
        {
            queue[j]=curr->left;
            j++;
        }
        if (curr->right!= nullptr)
        {
            queue[j]=curr->right;
            j++;
        }

    }

    //check if each element of other is found in this
    for (int idx=0;idx<i;idx++)
    {
        int found=0;
        Node *current=root;
        while (current!= nullptr)
        {
            if(current->info.first == elems[idx]->info.first){
                found++;
            }
            if(rel(elems[idx]->info.first, current->info.first)){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        if (found==0)
            return false;
    }
    return true;
}

void SortedMap::deleteRec(Node *parent) {
    if(parent == nullptr){
        return;
    }
    deleteRec(parent->left);
    deleteRec(parent->right);
    delete parent;
}

//worst=best=average=θ(n)
SortedMap::~SortedMap() {
    if (root!= nullptr)
        deleteRec(root);
}
