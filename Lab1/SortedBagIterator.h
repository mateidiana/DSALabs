//
// Created by Diana on 08-Mar-2024.
//

#ifndef LAB1_SORTEDBAGITERATOR_H
#define LAB1_SORTEDBAGITERATOR_H

#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
    friend class SortedBag;

private:
    const SortedBag& bag;
    SortedBagIterator(const SortedBag& b);
    SortedBagIterator(const SortedBag& b, int poz);

    //TODO - Representation
    int idx; //iterator for elements
    int freq_idx; //iterator for frequencies

public:
    TComp getCurrent();
    bool valid();
    void next();
    void next_generalised_iterator(int nr);
    void first();
};

#endif //LAB1_SORTEDBAGITERATOR_H
