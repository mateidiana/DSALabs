#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {

    MultiMap m;
    m.add(1,2);
    m.add(1,3);
    m.add(2,5);
    m.remove(1,3);
    m.remove(1,2);

    MultiMap m1;
    m1.add(1,5);
    m1.add(2,6);
    m1.add(2,8);
    m1.add(3,2);
    m1.add(3,3);
    m1.add(3,4);
    //m1.print();

//    vector<pair<TKey,int>> exvec;
//    exvec=m1.Occurences();
//    for (int i=0;i<exvec.size();i++)
//        cout<<exvec[i].first<<" "<<exvec[i].second<<"\n";

    testAll();
    testAllExtended();
    cout << "End" << endl;
    system("pause");

}

