#include <iostream>
#include "SparseMatrix.h"
using namespace std;


int main()
{
	SparseMatrix<int> matrix(3, 3);
	SparseMatrix<int> result(3, 3);

	matrix.InsertVal(1, 0, 0);
	matrix.InsertVal(3, 2, 0);
	matrix.InsertVal(2, 1, 1);
	matrix.InsertVal(1, 2, 2);

	//result = matrix + matrix;
	int val;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			val = matrix.GetVal(i, j);
			cout << val <<" ";
		}
		cout << endl;
	}
	int i;
	cin >> i;
	return 0;
}