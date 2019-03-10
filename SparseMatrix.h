#ifndef SPARSEMATRIX_H_
#define SPARSEMATRIX_H_

#include <iostream>
#include <vector>

using namespace std;

//CRS format sparse matrix storage
template <typename T>
class SparseMatrix {

public:
	//Initialization: Matrix size (nrows, ncols)
	SparseMatrix(int nrows, int ncols); 
	~SparseMatrix(void);

	//Insert value
	//Note: Index of col and row starts from 0; 
	//if val == 0, will remove element
	void InsertVal(T val, int row, int col);

	//Get value
	T GetVal(int row, int col) const;

	//matrix manupulation 
	//multiply
	SparseMatrix<T> operator *(const SparseMatrix<T> &matrix) const;
	//add
	SparseMatrix<T> operator +(const SparseMatrix<T> &matrix) const;

private:
	int ncols, nrows;
	vector <int> *cols, *rows;
	vector <T> *vals;
	//remove element
	void Remove(int pos, int row);
	//insert element
	void Insert(int pos, int row, int col, T val);
};

#include "SparseMatrix.cpp"

#endif // !SPARSEMATRIX_H_
#pragma once
