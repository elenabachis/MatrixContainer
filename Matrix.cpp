#include "Matrix.h"
#include <exception>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) { //Constructor

    if (nrCols <= 0 || nrLines <= 0) {
        throw exception();  //nrcols und nrlines durfen nicht negativ oder null sein
    }
    this->numLines = nrLines;
    this->numCols = nrCols;
    this->size = 1; //die Kapazitat die ich iniziell allokiere fur rows und values
    this->numElems = 0; //iniziell sind alle Elementen null
    this->columnIndex = new int[nrCols + 1]; //wir haben eine feste Grosse fur Spalten, also Splaten+1
    this->rows = new int[1]; //hat die Grosse size
    this->values = new TElem[1]; //hat auch die Grosse size

    for (int i = 0; i < nrCols + 1; i++) {
        columnIndex[i] = 0; //wir initialisieren dieses Array mit nullen
    }

}

// complexity: theta(1)
int Matrix::nrLines() const {
    return this->numLines; //gibt die Anzahl der Linien public zuruck
}


// complexity: theta(1)
int Matrix::nrColumns() const {
    return this->numCols; //gibt die Anzahl der Spalten public zuruck
}


TElem Matrix::element(int i, int j) const {

    if (i < 0 || i >= numLines || j < 0 || j >= numCols)  {
        throw exception(); //wenn i und j nicht das Intervall [0,numLines(numCols)-1] enstprechen
    }
    for (int k = columnIndex[j]; k < columnIndex[j + 1]; k++) { //sucht man in der Spalte j die Element aus der Zeile i
        if (rows[k] == i) {
            return values[k];
        }
    }
    return NULL_TELEM; //wenn das Element nicht gefunden ist, gibt es auf dieser Position ein NULL_TELEM

}

TElem Matrix::modify(int i, int j, TElem e) {
    if (j < 0 || j >= numLines || i < 0 || i >= numCols) {
        throw exception(); //wenn i und j nicht das Intervall [0,numLines(numCols)-1] enstprechen
    }

    // search for the position of the element in the rows array
    // if element is found it will be replaced with the oldValue

    for (int k = columnIndex[j]; k < columnIndex[j + 1]; k++) {
        if (rows[k] == i) {
            TElem old_value = values[k];  //man sucht den nicht nullen Element auf i und j
            values[k] = e;   //und ersetzt das Element mit e
            return old_value;  // das alte ELement wird zuruckgegeben
        }
    }

    if (numElems == size) {
        // the values array is full, we need to resize it
        int new_size = size * 2; //vergrossert(verdoppelt) man die Kapazitat von rows und values
        auto *new_values = new TElem[new_size];
        int *new_rows = new int[new_size]; //man allokiert neue Arrays mit der neuen Kapazitat

        for (int k = 0; k < numElems; k++) { //man kopiert alle bisherige Elemente von values und rows
            new_values[k] = values[k];
            new_rows[k] = rows[k];
        }

        delete[] values; //man deallokiert den Speicherplatz
        delete[] rows;
        values = new_values; //man stellt die neue Kapazitat fest
        rows = new_rows;
        size = new_size;
    }
    if (e!=0) {
        int pos = columnIndex[j + 1];
// shift the elements in the values and column arrays to the right from the index k up to the end of the column i+1
        for (int k = numElems; k > pos; k--) {
            values[k] = values[k - 1];
            rows[k] = rows[k - 1];
        }
        values[pos] = e;
        rows[pos] = i;
        columnIndex[j + 1]++;
        numElems++;     //ich habe ein neues Element auf der position pos eingefugt
    }
    return NULL_TELEM;
}


void Matrix::transpose(int i, int j, TElem e) {

    int row_num=i;
    int col_num=j;
    int **matrix = new int *[row_num]; //pointer of pointers
    for (i = 0; i < row_num; i++) {
        matrix[i] = new int[col_num];
    }
    for (i = 0; i < row_num; i++) {
        for (j = 0; j < col_num; j++) {
            matrix[j][i] = this->element(i,j);
        }
    }
}

Matrix::~Matrix() {  //Destructor
    delete[] columnIndex;
    delete[] rows;
    delete[] values;
}


