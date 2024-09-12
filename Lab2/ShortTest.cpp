#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include<iostream>

void testAll() {
    MultiMap m;
    m.add(1, 100);
    m.add(2, 200);
    m.add(3, 300);
    m.add(1, 500);
    m.add(2, 600);
    m.add(4, 800);

    assert(m.size() == 6);

    assert(m.remove(5, 600) == false);
    assert(m.remove(1, 500) == true);

    assert(m.size() == 5);

    vector<TValue> v;
    v=m.search(6);
    assert(v.size()==0);

    v=m.search(1);
    assert(v.size()==1);

    assert(m.isEmpty() == false);

    MultiMapIterator im = m.iterator();
    assert(im.valid() == true);

    while (im.valid()) {
        im.getCurrent();
        im.next();
    }
    assert(im.valid() == false);
    im.first();
    assert(im.valid() == true);


    MultiMap m1;
    m1.add(1,5);
    m1.add(2,6);
    m1.add(2,8);
    m1.add(3,2);
    m1.add(3,3);
    m1.add(3,4);
    //m1.print();

    vector<pair<TKey,int>> exvec;
    exvec=m1.Occurences();
    assert(exvec[0].first==3);
    assert(exvec[0].second==3);
    assert(exvec[1].first==2);
    assert(exvec[1].second==2);
    assert(exvec[2].first==1);
    assert(exvec[2].second==1);

}

