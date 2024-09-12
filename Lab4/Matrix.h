#pragma once

#include <iostream>

//DO NOT CHANGE THIS PART
typedef int TElem;
class Iterator;
#define NULL_TELEM 0

//3. Matrix auf Hashtabelle mit offener Addressierung mit doppeltem Hashing
//3. Matrix as hashtable with open addressing with double hashing

struct matrixElement{
    int row;
    int col;
    TElem val;
};

class Matrix {

    friend class Iterator;

private:
    int numberRows;
    int numberColumns;
    matrixElement* hashTable;
    int capacity;
    int nrElems;

    int hashFunc(int row, int col, int i) const{
        return ((hashFunc1(row,col) + i * hashFunc2(row,col)) % capacity);
    }

    int hashFunc1(int row, int col) const{
        return (row*numberColumns+col)%(capacity-1);
    }

    int hashFunc2(int row, int col) const{
        return 1+((row*numberColumns+col)%(capacity-1));
    }

    void resizeRehash();

public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    int generatePrime(int x);

    bool isPrime(int x);

    Iterator iterator() const;

    void print();

    // destructor
    ~Matrix();

};
