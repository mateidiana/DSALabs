#include "Matrix.h"
#include "Iterator.h"
#include <exception>
using namespace std;

//worst=best=average=θ(n)
Matrix::Matrix(int nrLines, int nrCols) {
    numberRows = nrLines;
    numberColumns = nrCols;

    capacity = 11;
    nrElems=0;
    hashTable = new matrixElement[capacity];

    for (int i = 0; i < capacity; i++) {
        hashTable[i].row = -1;
        hashTable[i].col = -1;
        hashTable[i].val = NULL_TELEM;
    }
}

bool Matrix::isPrime(int x) {
    if (x<=1)
        return false;
    for (int i=2;i*i<=x;i++)
        if (x%i==0)
            return false;
    return true;
}

int Matrix::generatePrime(int x) {
    while(!isPrime(x))
        x++;
    return x;
}

//best=worst=average=θ(n)
void Matrix::resizeRehash() {

    int old_capacity = capacity;
    capacity= generatePrime(capacity*2);
    matrixElement *newElems = new matrixElement[capacity];

    for (int index = 0; index < capacity; index++) {
        newElems[index].row = -1;
        newElems[index].col = -1;
        newElems[index].val = NULL_TELEM;
    }

    for (int index = 0; index < old_capacity; index++) {

        if (hashTable[index].val != NULL_TELEM && hashTable[index].val != NULL_TELEM-1) {
            int pos = 0;
            int position = hashFunc(hashTable[index].row,hashTable[index].col, pos);

            while (newElems[position].val != NULL_TELEM) {
                pos++;
                position = hashFunc(hashTable[index].row,hashTable[index].col, pos);
            }
            newElems[position] = hashTable[index];
        }
    }

    delete[] hashTable;
    hashTable = newElems;
}

//worst=best=average=θ(1)
int Matrix::nrLines() const {
    return numberRows;
}

//worst=best=average=θ(1)
int Matrix::nrColumns() const {
    return numberColumns;
}

//best=θ(1)
//worst=θ(n)
//average=θ(1)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || j < 0 || i >= numberRows || j >= numberColumns)
        throw exception();

    int pos = 0;
    int position = hashFunc(i,j, pos);

    while (pos < capacity && hashTable[position].val != NULL_TELEM) {

        if (hashTable[position].val != NULL_TELEM && hashTable[position].val != NULL_TELEM-1 && hashTable[position].row == i && hashTable[position].col == j) {
            return hashTable[position].val;
        }
        pos++;
        position = hashFunc(i,j, pos);
    }
    return NULL_TELEM;
}

//best=θ(1)
//worst=θ(n)
//average=θ(1)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i >= numberRows || j >= numberColumns) {
        throw exception();
    }

    if (element(i, j)) {
        int pos = 0;
        int position = hashFunc(i,j, pos);

        while (pos < capacity) {
            if (hashTable[position].val != NULL_TELEM && hashTable[position].val != NULL_TELEM-1 &&
                hashTable[position].row == i && hashTable[position].col == j) {

                TElem oldData = hashTable[position].val;
                if (e != NULL_TELEM) {
                    hashTable[position].val = e;
                }
                else {
                    hashTable[position].val = NULL_TELEM-1;
                    hashTable[position].row=-1;
                    hashTable[position].col=-1;
                    nrElems--;
                }
                return oldData;
            }
            pos++;
            position = hashFunc(i,j, pos);
        }
    }
    else{
        if (e == NULL_TELEM)
            return NULL_TELEM;

        int pos = 0;
        int position = hashFunc(i,j, pos);

        while (pos < capacity && hashTable[position].val != NULL_TELEM && hashTable[position].val != NULL_TELEM-1) {
            pos++;
            position = hashFunc(i ,j, pos);
        }

        if (pos < capacity && hashTable[position].val == NULL_TELEM || hashTable[position].val == NULL_TELEM-1) {
            hashTable[position].val = e;
            hashTable[position].row = i;
            hashTable[position].col = j;
            nrElems++;
            return NULL_TELEM;
        }

        else {
            resizeRehash();
            return modify(i, j, e);
        }
    }
}

void Matrix::print()
{
    for (int i=0;i<capacity;i++)
        if (hashTable[i].val!=NULL_TELEM && hashTable[i].val!=NULL_TELEM-1)
            cout<<hashTable[i].row<<","<<hashTable[i].col<<": "<<hashTable[i].val<<"\n";
}

//worst=best=average=θ(1)
Iterator Matrix::iterator() const {
    return Iterator(*this);
}

//worst=best=average=θ(1)
Matrix::~Matrix() {
    delete[] hashTable;
}


