#include "Iterator.h"
#include "Matrix.h"

//Specification
//pre matrix m
//post index for rows and columns is 0, sorted arrays for rows and columns
//best=worst=average=θ(1)
Iterator::Iterator(const Matrix& m): mat(m) {

    indexRows=0;
    indexColumns=0;
    size=m.nrElems;
    elemsRows=new matrixElement[size];
    elemsColumns=new matrixElement[size];
    int index1=0;
    for (int i=0;i<m.capacity;i++)
        if (m.hashTable[i].val!=NULL_TELEM&&m.hashTable[i].val!=NULL_TELEM-1)
        {
            elemsRows[index1]=m.hashTable[i];
            elemsColumns[index1]=m.hashTable[i];
            index1++;
        }
    sortRows();
    sortColumns();
}

//pre iterator i
//post elem is element on position i
//best=worst=average=θ(1)
TElem Iterator::getCurrentRows() const {
    return elemsRows[indexRows].val;
}

//best=worst=average=θ(1)
TElem Iterator::getCurrentColumns() const {
    return elemsColumns[indexColumns].val;
}

//pre iterator i
//post true/false if i valid
//best=worst=average=θ(1)
bool Iterator::valid() const {
    if (indexRows>=0 && indexRows<size && indexColumns>=0 && indexColumns<size)
        return true;
    return false;
}

//pre iterator i
//post i on next position
//best=worst=average=θ(1)
void Iterator::nextRows() {
    if (valid())
        indexRows++;
}

//best=worst=average=θ(1)
void Iterator::nextColumns() {
    if (valid())
        indexColumns++;
}

//pre iterator i on position p
//post iterator i on position 0
//best=worst=average=θ(1)
void Iterator::firstRows() {
    indexRows=0;
}

//best=worst=average=θ(1)
void Iterator::firstColumns() {
    indexColumns=0;
}

//pre array of elements in matrix
//post array sorted by rows
//best=worst=average=θ(n^2)
void Iterator::sortRows() {
    matrixElement aux;

    for (int i=0;i<size-1;i++)
        for (int j=i+1;j<size;j++)
            if (elemsRows[i].row>elemsRows[j].row)
            {
                aux=elemsRows[i];
                elemsRows[i]=elemsRows[j];
                elemsRows[j]=aux;
            }

    for (int i=0;i<size-1;i++)
        for (int j=i+1;j<size;j++)
            if (elemsRows[i].col>elemsRows[j].col && elemsRows[i].row==elemsRows[j].row)
            {
                aux=elemsRows[i];
                elemsRows[i]=elemsRows[j];
                elemsRows[j]=aux;
            }
}

//pre array of elements in matrix
//post array sorted by columns
//best=worst=average=θ(n^2)
void Iterator::sortColumns() {
    matrixElement aux;

    for (int i=0;i<size-1;i++)
        for (int j=i+1;j<size;j++)
            if (elemsColumns[i].col>elemsColumns[j].col)
            {
                aux=elemsColumns[i];
                elemsColumns[i]=elemsColumns[j];
                elemsColumns[j]=aux;
            }

    for (int i=0;i<size-1;i++)
        for (int j=i+1;j<size;j++)
            if (elemsColumns[i].row>elemsColumns[j].row && elemsColumns[i].col==elemsColumns[j].col)
            {
                aux=elemsColumns[i];
                elemsColumns[i]=elemsColumns[j];
                elemsColumns[j]=aux;
            }

}


