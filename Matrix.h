#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    int numLines; //die Anzahl der Linien
    int numCols; //die Anzahl der Spalten
    int size; //die Kapazitat fur rows
    int numElems; //die Anzahl der non nullen Elementen des Matrizes
    int *columnIndex; //die Indizen der ersten nicht nullen Werten,mit der die Spalte beginnt
    int *rows; //die Indizen der Linien wo eine non-null Wert steht
    TElem *values; //die non-nullen Elemeneten des Matrizes
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line j and rows i (indexing starts from 0)
	//throws exception if (j,i) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line j and rows i
	//returns the previous value from the position
	//throws exception if (j,i) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    void transpose(int i, int j, TElem e);
	// destructor
	~Matrix();

};
