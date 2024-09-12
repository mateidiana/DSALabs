#include <iostream>
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
using namespace std;

//worst=best=average=θ(n)
IteratedList::IteratedList() {
    head=-1;
    nrelems=0;
    capacity=99;
    array=new Node[capacity];
    firstEmpty=0;
    for (int i=0;i<capacity;i++)
    {
        array[i].next=i+1;
    }
    array[capacity-1].next=-1;

}

//worst=best=average=θ(n)
int IteratedList::size() const {
    ListIterator it=first();
    int count=0;
    while(it.valid())
    {
        count++;
        it.next();
    }
    return count;

}

//worst=best=average=θ(1)
bool IteratedList::isEmpty() const {
    return head==-1;
}

//worst=best=average=θ(1)
ListIterator IteratedList::first() const {
    ListIterator it(*this);
    it.first();
    return it;
}

//worst=best=average=θ(1)
TElem IteratedList::getElement(ListIterator pos) const {
    if (!pos.valid())
        throw exception();
    return pos.getCurrent();
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
TElem IteratedList::remove(ListIterator& pos) {
    if (!pos.valid())
        throw exception();
    int removedNode=pos.current;
    TElem removedData=array[removedNode].value;

    if (removedNode==head)
    {
        head=array[head].next;
        pos.next();
        array[removedNode].next=firstEmpty;
        firstEmpty=removedNode;
        nrelems--;

        if (nrelems*4 == capacity && !isEmpty())
            resize_down();

        return removedData;
    }

    auto it = first();
    while (array[it.current].next != removedNode)
        it.next();

    array[it.current].next = array[removedNode].next;
    pos.next();
    array[removedNode].next = firstEmpty;
    firstEmpty = removedNode;
    nrelems--;

    if (nrelems*4 == capacity && !isEmpty())
        resize_down();

    return removedData;
}

//best=θ(1)
//worst=θ(n*n1) sizes of both lists
//average=θ(n*n1)
void IteratedList::removeOccurences(IteratedList list1) {
    ListIterator itCurrent=first();
    int found;
    while(itCurrent.valid())
    {
        found=0;

        ListIterator it1=list1.first();
        while(it1.valid())
        {
            if (itCurrent.getCurrent()==it1.getCurrent())
            {
                found=1;
                break;
            }

            it1.next();
        }
        if (found==1)
        {
            int removedNode=itCurrent.current;

            if (removedNode==head)
            {
                head=array[head].next;
                itCurrent.next();
                array[removedNode].next=firstEmpty;
                firstEmpty=removedNode;
                nrelems--;

                if (nrelems*4 == capacity && head!=-1)
                    resize_down();


            }
            else{
                auto it = first();
                while (array[it.current].next != removedNode)
                    it.next();

                array[it.current].next = array[removedNode].next;
                itCurrent.next();
                array[removedNode].next = firstEmpty;
                firstEmpty = removedNode;
                nrelems--;

                if (nrelems*4 == capacity && head!=-1)
                    resize_down();
            }

        }
        else
            itCurrent.next();
    }

}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
ListIterator IteratedList::search(TElem e) const{
    ListIterator it=first();
    while(it.valid())
    {
        if (it.getCurrent()==e)
            return it;
        it.next();
    }
    //return invalid iterator
    return it;
}

//worst=best=average=θ(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if (!pos.valid())
        throw exception();
    TElem oldData=pos.getCurrent();
    array[pos.current].value=e;
    return oldData;
}

//worst=best=average=θ(1)
void IteratedList::addToBeginning(TElem e) {
    if (nrelems==capacity)
        resize_up();

    int aux=array[firstEmpty].next;
    array[firstEmpty] = Node{e, head};
    head = firstEmpty;
    firstEmpty = aux;
    nrelems++;
}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if (nrelems==capacity)
        resize_up();

    if (!pos.valid())
        throw std::exception();

    if (head==-1)
    {
        head=0;
        firstEmpty=1;
        array[head].value=e;
        array[head].next=-1;
        nrelems++;
    }
    else
    if (array[pos.current].next==-1)
    {
        addToEnd(e);
        pos.first();
        while(array[pos.current].next!=-1)
            pos.next();
    }
    else
    {
        int aux;
        aux=array[firstEmpty].next;
        array[firstEmpty].value=e;
        array[firstEmpty].next=array[pos.current].next;
        array[pos.current].next=firstEmpty;
        firstEmpty=aux;
        nrelems++;
        pos.next();
    }

}

//best=θ(1)
//worst=θ(n)
//average=θ(n)
void IteratedList::addToEnd(TElem e) {
    if (nrelems==capacity)
        resize_up();

    if(isEmpty()){
        head = firstEmpty;
        firstEmpty = array[firstEmpty].next;
        array[head].value = e;
        array[head].next = -1;
        nrelems++;
        return;
    }

    int aux;
    ListIterator it(*this);
    it.first();
    while(array[it.current].next!=-1)
        it.next();

    array[firstEmpty].value=e;
    aux=array[firstEmpty].next;
    array[firstEmpty].next=-1;
    array[it.current].next=firstEmpty;
    firstEmpty=aux;
    nrelems++;

}

//worst=best=average=θ(n)
void IteratedList::resize_up()
{
    int newCapacity=capacity*3;
    auto newArray=new Node[newCapacity];

    for (int index=0;index<capacity;index++)
    {
        newArray[index].value=array[index].value;
        newArray[index].next=array[index].next;
    }

    for (int index=capacity;index<newCapacity;index++)
        newArray[index].next=index+1;
    newArray[newCapacity-1].next=-1;
    firstEmpty=capacity;

    delete[] array;

    array=newArray;
    capacity=newCapacity;
}

//worst=best=average=θ(n)
void IteratedList::resize_down()
{
    int newCapacity=capacity/2;
    auto newArray=new Node[newCapacity];

    ListIterator it=first();
    int index=0;
    while(it.valid())
    {
        newArray[index].value=array[it.current].value;
        newArray[index].next=array[it.current].next;
        index++;
        it.next();
    }

    for (int i=nrelems;i<newCapacity;i++)
        newArray[i].next=i+1;

    newArray[newCapacity-1].next=-1;
    firstEmpty=nrelems;
    head=0;

    delete[] array;

    array=newArray;
    capacity=newCapacity;

}

void IteratedList::print() {
    ListIterator it=first();
    while(it.valid())
    {
        cout<<it.getCurrent()<<" ";
        it.next();
    }
}


//worst=best=average=θ(1)
IteratedList::~IteratedList() {
    delete[] array;
}
