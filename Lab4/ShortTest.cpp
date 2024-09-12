#include <assert.h>
#include "Matrix.h"
#include "Iterator.h"

using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);


    Matrix m1(3,3);
    m1.modify(0,0,1);
    m1.modify(1,1,3);
    m1.modify(0,2,3);
    m1.modify(0,1,2);
    m1.modify(1,0,5);
    m1.modify(2,0,4);
    Iterator im=m1.iterator();
    im.firstRows();
    assert(im.getCurrentRows()==1);
    im.nextRows();
    assert(im.getCurrentRows()==2);
    im.nextRows();
    im.nextRows();
    assert(im.getCurrentRows()==5);

    im.firstColumns();
    assert(im.getCurrentColumns()==1);
    im.nextColumns();
    assert(im.getCurrentColumns()==5);
    im.nextColumns();
    assert(im.getCurrentColumns()==4);
    im.nextColumns();
    assert(im.getCurrentColumns()==2);
}