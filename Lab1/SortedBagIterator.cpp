//
// Created by Diana on 08-Mar-2024.
//

#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//worst=average=best=θ(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    idx=0;
    freq_idx=0;
}

//worst=average=best=θ(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b,int poz) : bag(b) {
    idx=poz;
    freq_idx=0;
}

//worst=best=average=θ(1)
TComp SortedBagIterator::getCurrent() {
    if (valid()) {
        return bag.elems[idx].elem;
    } else throw exception();
}

//worst=best=average=θ(1)
bool SortedBagIterator::valid() {
    if (idx >=0 && idx < bag.length)
        return true;

    return false;
}

//worst=best=average=θ(1)
void SortedBagIterator::next() {
    if (valid())
    {
        if (freq_idx == bag.elems[idx].freq - 1)
        {
            idx++;
            freq_idx=0;
        }
        else
        if (freq_idx<bag.elems[idx].freq-1)
            freq_idx++;
    }
    else
        throw exception();
}

//worst=best=average=θ(1)
void SortedBagIterator::next_generalised_iterator(int nr) {
    if (nr>0)
    {
        if (idx>=0 && idx < bag.length) //valid()
        {
            if (freq_idx+nr<bag.elems[idx].freq)
                freq_idx+=nr;
            else {
                int temp=nr-bag.elems[idx].freq;
                idx++;
                freq_idx=temp;
            }
        }
        else
        {
            throw exception();
        }
    }
    if(nr<0){
        if (idx>=0 && idx < bag.length)
        {
            if (freq_idx+nr>=0)
                freq_idx+=nr;
            else{
                int temp=bag.elems[idx].freq+nr;
                idx--;
                freq_idx=temp+bag.elems[idx].freq;
            }
        }
        else{
            throw exception();
        }
    }

}

//worst=best=average=θ(1)
void SortedBagIterator::first() {
    idx=0;
}


