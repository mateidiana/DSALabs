#include <iostream>
#include <cassert>
#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll(){
    SortedMap sm(relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
        TElem e = it.getCurrent();
        assert(e.second != NULL_TVALUE);
        it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());

    SortedMap anotherMap(relatie1);
    anotherMap.add(25,1);
    anotherMap.add(20,1);
    anotherMap.add(10,1);
    anotherMap.add(22,1);
    anotherMap.add(14,1);
    anotherMap.add(12,1);
    anotherMap.add(30,1);
    anotherMap.add(35,1);


    SMIterator it2=anotherMap.iterator();
    it2.first();
    while(it2.valid())
    {
        //cout<<it2.getCurrent().first<<" ";
        it2.next();
    }
    //cout<<"\n\n";

    SortedMap map1(relatie1);
    map1.add(1,5);
    map1.add(2,3);
    map1.add(4,8);

    SortedMap map2(relatie1);
    map2.add(1,5);
    map2.add(2,3);
    map2.add(4,8);
    //map2.add(7,9);
    assert(map1==map2);
}

