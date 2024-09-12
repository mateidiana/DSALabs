#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

//worst=θ(n)
//best=θ(log n)
//average=θ(log n)
SMIterator::SMIterator(const SortedMap& m) : map(m){
    current= nullptr;
    first();
}

//worst=θ(n)
//best=θ(log n)
//average=θ(log n)
void SMIterator::first(){
    //Empty the stack
    while (!nodeStack.isEmpty()) {
        nodeStack.pop();
    }

    //Push all elements going left into the stack
    //First is the last inserted element, the one from the farthest left
    current = map.root;
    while (current != nullptr) {
        nodeStack.push(current);
        current = current->left;
    }
    if (!nodeStack.isEmpty()) {
        current = nodeStack.top();
        nodeStack.pop();
    } else {
        current = nullptr;
    }
}

//worst=θ(n)
//best=θ(1)
//average=θ(1)
void SMIterator::next(){
    if (!valid()) {
        throw exception();
    }
    if (current->right != nullptr) {
        current = current->right;
        while (current != nullptr) {
            nodeStack.push(current);
            current = current->left;
        }
    }
    if (!nodeStack.isEmpty()) {
        current = nodeStack.top();
        nodeStack.pop();
    } else {
        current = nullptr;
    }
}

//worst=best=average=θ(1)
bool SMIterator::valid() const{
    return current != nullptr;
}

//worst=best=average=θ(1)
TElem SMIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }
    return current->info;
}

SMIterator::Stack::Stack() {
    //Initialise array of nodes
    capacity = 10;
    nrElems = 0;
    data = new Node * [capacity];
}

void SMIterator::Stack::push(Node * t) {
    if (nrElems == capacity) {
        resizeUp();
    }
    data[nrElems++] = t;
}

void SMIterator::Stack::pop() {
    if(nrElems > 0) {
        nrElems--;
    }
}

Node* SMIterator::Stack::top() {
    if (nrElems > 0) {
        return data[nrElems - 1];
    }
    return nullptr;
}

bool SMIterator::Stack::isEmpty() const {
    return (nrElems == 0);
}

void SMIterator::Stack::resizeUp() {
    capacity *= 2;
    Node** newData = new Node*[capacity];
    for (int i = 0; i < nrElems; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

SMIterator::Stack::~Stack() {
    delete[] data;
}


