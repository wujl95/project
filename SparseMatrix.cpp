#include "SparseMatrix.h"

#ifndef SPARSEMATRIX_IMPL_
#define SPARSEMATRIX_IMPL_

//-----Initialize SparseMatrix-----
template <typename T>
SparseMatrix<T>::SparseMatrix(int nrows, int ncols)
{
	if ((ncols < 1) || (nrows < 1))
	{
		cout << "Cannot Initialize Matrix with zero or negative size.";
		cout << "Enter number of columns (>=1)";
		cin >> ncols;
		cout << "Enter number of rows (>=1)";
		cin >> nrows;
	}
	this->ncols = ncols;
	this->nrows = nrows;
	this->cols = NULL;
	this->vals = NULL;
	this->rows = new vector<int>(nrows + 1, 0);
}


template <typename T>
SparseMatrix<T>::~SparseMatrix(void)
{
	if ((this->vals) != NULL)
	{
		delete this->vals;
		delete this->cols;
	}
	delete this->rows;
}


//-----get or insert values-----
template <typename T>
void SparseMatrix<T>::InsertVal(T val, int row, int col)
{
	if (col > (this->ncols - 1) || col < 0 || row > (this->nrows - 1) || row < 0)
	{
		cout << "Invalid col/row index";
		throw 0;
	}

	int currcol = -1; 
	int pos = (*(this->rows))[row];

	//get the position index where value should be inserted for this->cols and this->vals vector
	for (; pos < (*(this->rows))[row + 1]; pos++)
	{
		currcol = (*(this->cols))[pos];
		if (currcol >= col) break;
	}

	//insert value at vals[pos], cols[pos]
	if (!(val == T())) //if the element to be added is not zero
	{
		if (!(currcol == col)) //if col and row does not exist
		{
			this->Insert(pos, row, col, val); 
		}
		else //if the col and row already existed
		{
			(*(this->vals))[pos] = val; //update value
		}
	}
	else //if the element to be added is zero
	{
		if (currcol == col) //if col and row already existed
		{
			this->Remove(pos, row);
		}
		else
		{
			return; //if element to be added is zero and col and row does not exist, exit;
		}
	}
}

template <typename T>
void SparseMatrix<T>::Remove(int pos, int row)
{
	this->cols->erase(this->cols->begin() + pos);
	this->vals->erase(this->vals->begin() + pos);
	for (int i = row + 1; i <= this->nrows +1; i++)
	{
		(*(this->rows))[i] -= 1;
	}
}

template <typename T>
void SparseMatrix<T>::Insert(int pos, int row, int col, T val)
{
	if ((this->vals) == NULL)
	{
		this->vals = new vector<T>(1, val);
		this->cols = new vector<int>(1, col);
	}
	else
	{
		this->vals->insert(this->vals->begin() + pos, val);
		this->cols->insert(this->cols->begin() + pos, col);
	}
	for (int i = row + 1; i < this->nrows +1; i++)
	{
		(*(this->rows))[i] += 1;
	}
}

template <typename T>
T SparseMatrix<T>::GetVal(int row, int col) const
{
	int currcol;
	//locate index range in this->vals and this->cols vector using position idicator from this->rows vector
	for (int pos = (*(this->rows))[row]; pos < (*(this->rows))[row + 1]; pos++) 
	{
		currcol = (*(this->cols))[pos];
		if (currcol > col)
		{
			break;
		}
		else if (currcol == col)
		{
			return (*(this->vals))[pos];
		}
	}
	return T();
}

//this * matrix
template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator *(const SparseMatrix<T> &matrix) const
{
	//if dimension does not match
	if (!((this->ncols) == (matrix.ncols)))
	{
		cout << "Dimensions does not match.";
		throw 0;
	}

	T value;
	int col_idx;
	SparseMatrix<T> result(this->nrows, matrix.ncols);

	for (int i = 0; i < this->nrows; i++)
	{
		for (int j = 0; j < matrix.ncols; j++)
		{
			value = T();
			for (int k = (*(this->nrows))[i]; k < (*(this->nrows))[i + 1]; k++) //iterate to add only non-zero values
			{
				col_idx = (*(this->cols))[k];
				value = value + (this->GetVal(i, col_idx))*(matrix->GetVal(col_idx, j));
			}
			result->InsertVal(value, i, j);
		}
	}
	return result;
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator +(const SparseMatrix<T> &matrix) const
{
	if (!(this->ncols == matrix.ncols) || !(this->nrows == matrix.nrows))
	{
		cout << "Dimensions does not match.";
		throw 0;
	}

	T value;
	int col_idx;

	SparseMatrix<T> result(this->nrows, this->ncols);

	for (int i = 0; i < this->nrows; i++)
	{
		for (int j = (*(this->rows))[i]; j < (*(this->rows))[i + 1]; j++)
		{
			col_idx = (*(this->cols))[j];
			value = this->GetVal(i, col_idx) + matrix.GetVal(i, col_idx);
			result.InsertVal(value, i, col_idx);
		}
	}
	return result;
}
#endif // !SPARSEMATRIX_IMPL_