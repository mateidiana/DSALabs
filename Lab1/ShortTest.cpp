//
// Created by Diana on 08-Mar-2024.
//
#include <iostream>
#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
using namespace std;

bool relation1(TComp e1, TComp e2) {
    return e1 <= e2;
}

void testAll() {
    SortedBag sb(relation1);
    sb.add(5);
    sb.add(6);
    sb.add(0);
    sb.add(5);
    sb.add(10);
    sb.add(8);

    assert(sb.size() == 6);
    assert(sb.nrOccurrences(5) == 2);

    assert(sb.remove(5) == true);
    assert(sb.size() == 5);

    assert(sb.search(6) == true);
    assert(sb.isEmpty() == false);

    SortedBagIterator it = sb.iterator();
    assert(it.valid() == true);
    while (it.valid()) {
        it.getCurrent();
        it.next();
    }
    assert(it.valid() == false);
    it.first();
    assert(it.valid() == true);

    SortedBag testbag(relation1);
    testbag.add(2);
    testbag.add(2);
    testbag.add(2);
    testbag.add(4);
    testbag.add(4);
    testbag.add(5);
    testbag.add(6);
    testbag.add(6);
    SortedBagIterator iter=testbag.iterator(0);
    assert(iter.valid()==true);
    assert(iter.getCurrent()==2);
    iter.next_generalised_iterator(1);
    iter.next_generalised_iterator(1);
    iter.next_generalised_iterator(2);
    assert(iter.getCurrent()==4);
    iter.next_generalised_iterator(-1);
    assert(iter.getCurrent()==2);




}


