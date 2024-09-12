#pragma once
#include "Matrix.h"

class Matrix;

class Iterator
{
    friend class Matrix;

private:
    const Matrix& mat;

    Iterator(const Matrix& m);

    int indexRows;
    int indexColumns;
    int size;
    matrixElement *elemsRows;
    matrixElement *elemsColumns;

public:
    TElem getCurrentRows()const;
    TElem getCurrentColumns()const;
    bool valid() const;
    void nextRows();
    void nextColumns();
    void firstRows();
    void firstColumns();
    void sortRows();
    void sortColumns();
};
