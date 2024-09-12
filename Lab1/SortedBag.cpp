//
// Created by Diana on 08-Mar-2024.
//

#include "SortedBag.h"
#include "SortedBagIterator.h"

//worst=best=average=θ(1)
SortedBag::SortedBag(Relation r) {
    cap=10;
    length=0;
    rel=r;
    elems=new TElem[cap];
}

//O(n)
//best=θ(1) element already exists
//worst=θ(n) element needs to be inserted on first position
//average=θ(n)
void SortedBag::add(TComp e) {

    if (length == cap) resize(2);

    int insertIndex = BinarySearch(e);

    if (insertIndex != -1) {
        elems[insertIndex].freq++;
    }

    else {
        insertIndex = 0;
        while (rel(elems[insertIndex].elem, e) && insertIndex < length)
            insertIndex++;

        length++;

        for (int index = length - 1; index > insertIndex; index--)
            elems[index] = elems[index - 1];


        elems[insertIndex].elem = e;
        elems[insertIndex].freq = 1;
    }

}

//O(n)
//best=θ(1) if freq only needs to be decreased
//worst=θ(n) if all elements need to be shifted to the left (if first elem is deleted)
//average=θ(n)
bool SortedBag::remove(TComp e) {

    int removeIndex = BinarySearch(e);

    if (removeIndex == -1) return false;

    if (elems[removeIndex].freq>1)
        elems[removeIndex].freq--;

    else {
        for (int index = removeIndex; index < length - 1; index++)
            elems[index] = elems[index + 1];

        length--;

        if (length * 4 < cap)
            resize(0.5);
    }
    return true;
}

//O(log n)
//best=θ(1)
//worst=θ(log n)
//average=θ(log n)
bool SortedBag::search(TComp elem) const {
    if (BinarySearch(elem) != -1)
        return true;
    return false;

}

//O(log n)
//best=θ(1)
//worst=θ(log n)
//average=θ(log n)
int SortedBag::nrOccurrences(TComp elem) const {
    int index = BinarySearch(elem);

    if (index == -1) return 0;

    return elems[index].freq;
}


//worst=best=average=best=θ(n)
int SortedBag::size() const {
    int bagSize = 0;

    for (int index = 0; index < length; index++)
        bagSize += elems[index].freq;

    return bagSize;
}

//worst=best=average=best=θ(1)
bool SortedBag::isEmpty() const {
    return length == 0;
}

//worst=best=average=best=θ(1)
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

SortedBagIterator SortedBag::iterator(int poz) const {
    return SortedBagIterator(*this);
}

//worst=best=average=best=θ(n)
void SortedBag::resize(float multiplier) {
    cap *= multiplier;

    auto *newElems = new TElem[cap];

    for (int index = 0; index < length; index++)
        newElems[index] = elems[index];

    delete[] elems;
    elems = newElems;
}

//O(log n)
//best=θ(1)
//worst=θ(log n)
//average=θ(log n)
int SortedBag::BinarySearch(TComp el) const {
    int low,high,mid;
    low=0;
    high=length-1;
    mid=0;

    while (low<=high)
    {
        mid = (low + high) / 2;
        if (elems[mid].elem == el)
            return mid;
        else if (rel(elems[mid].elem, el))
            low = mid + 1;
        else
            high = mid - 1;

    }
    return -1;
}

//worst=average=best=θ(1)
SortedBag::~SortedBag() {
    delete[] elems;
}

