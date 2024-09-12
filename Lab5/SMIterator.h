#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
    friend class SortedMap;
private:

    const SortedMap& map;
    SMIterator(const SortedMap& mapionar);

    Node *current;

    class Stack{
    private:
        Node** data;
        int capacity;
        int nrElems;
        void resizeUp();

    public:
        Stack();
        void push(Node *t);
        void pop();
        Node* top();
        bool isEmpty() const;
        ~Stack();
    };

    Stack nodeStack;

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};

