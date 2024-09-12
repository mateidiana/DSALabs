#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
using namespace std;

//best=worst=average=θ(1)
ListIterator::ListIterator(const IteratedList& list) : list(list) {
    current=list.head;
}

//best=worst=average=θ(1)
void ListIterator::first() {
    current=list.head;
}

//best=worst=average=θ(1)
void ListIterator::next() {
    if (valid())
        current=list.array[current].next;
    else
        throw exception();
}

//best=worst=average=θ(1)
bool ListIterator::valid() const {
    if (current==-1)
        return false;
    return true;
}

//best=worst=average=θ(1)
TElem ListIterator::getCurrent() const {
    if (valid())
        return list.array[current].value;
    else
        throw exception();
}





