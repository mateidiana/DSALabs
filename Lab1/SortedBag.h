//
// Created by Diana on 08-Mar-2024.
//

#ifndef LAB1_SORTEDBAG_H
#define LAB1_SORTEDBAG_H


#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

//7. ADT Sorted Bag mit Elementen vom Typ TComp reprasentiert mit Hilfe eines dynamischen Arrays
//von Paaren der Form (Element, Frequenz), sortiert mit Hilfe einer Relation auf Elementen

//7. ADT Sorted Bag represented as a dynamic array of pairs (element, frequency), sorted by a relation

class SortedBag {
    friend class SortedBagIterator;

private:
    //TODO - Representation
    struct TElem {
        TComp elem;
        int freq;
    };

    TElem *elems;       //dynamic array of pairs
    int cap;           //total capacity
    int length;       //number of current elements
    Relation rel;    //relation between TComp elements

    void resize(float multiplier);
    int BinarySearch(TComp el) const;

public:
    //constructor
    SortedBag(Relation r);

    //adds an element to the sorted bag
    void add(TComp e);

    //removes one occurence of an element from a sorted bag
    //returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
    bool remove(TComp e);

    //checks if an element appears is the sorted bag
    bool search(TComp e) const;

    //returns the number of occurrences for an element in the sorted bag
    int nrOccurrences(TComp e) const;

    //returns the number of elements from the sorted bag
    int size() const;

    //returns an iterator for this sorted bag
    SortedBagIterator iterator() const;

    SortedBagIterator iterator(int poz) const;

    //checks if the sorted bag is empty
    bool isEmpty() const;

    //destructor
    ~SortedBag();
};


#endif //LAB1_SORTEDBAG_H
