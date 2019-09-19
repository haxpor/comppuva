/**
 * Matrix multiplication program (2D dynamic array implementation).
 * Input:
 *  M N separated by a space wheres M is number of elements in rows, and N is for column for first matrix.
 *  Then the following subsequent lines followed by element integer value row by row from left
 *  to right in each column. Each element separated by a space from column to another. Each row
 *  separated by a new line.
 *  Then N P again, this time for second matrix. And the similar pattern in subsequent lines
 *  for element values.
 *
 * Output:
 *  Output matrix element by element starting from row by row, left to right for column.
 *  Separate each element from column to another column by space, and each row by a new line.
 *
 * Use testcases/MatrixMultiplication1.txt, testcases/MatrixMultiplication2.txt, and
 * testcases/MatrixMultiplication3.txt as input.
 */
#include <iostream>

using namespace std;

/**
 * Multiply two matrix together A*B then return result which created on heap.
 * Call site has responsibility to destroy return resultant matrix when done using.
 *
 * This is column-major operation.
 *
 * \param a Matrix a in 2D array.
 * \param m Number of rows of matrix a
 * \param n Number of columns of matrix a
 * \param b Matrix b in 2D array.
 * \param p Number of rows of matrix b
 * \param q Number of columns of matrix b
 *
 * \return Resultant matrix which created on heap. If n != p or any of m,n,p,q is 0 or negative value,
 *         then return nullptr.
 */
static int** MatrixMultiply(const int* const * a, int m, int n, const int* const * b, int p, int q)
{
    if (m <= 0 ||
        n <= 0 ||
        p <= 0 ||
        q <= 0)
        return nullptr;
    if (n != p)
        return nullptr;

    // at the same time initialize the whole dynamic array to 0
    int** r = new int*[m];
    for (int i=0; i<m; ++i)
    {
        r[i] = new int[q]();
    }

    for (int i=0; i<m; ++i)
    {
        for (int j=0; j<q; ++j)
        {
            for (int k=0; k<n; ++k)
            {
                r[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return r;
}

static void Delete2DDynamicArray(int*** arr, int row)
{
    // delete[] array of columns
    for (int i=0; i<row; ++i)
    {
        delete[] (*arr)[i];
    }
    // delete[] all rows
    delete[] *arr;

    // affect variable at call site, now it becomes nullptr
    arr = nullptr;
}

int main ()
{
    int m, n, p, q;
    int** A = nullptr;
    int** B = nullptr;
    
    cin >> m >> n;

    // allocate 2D array for matrix A
    A = new int*[m];
    for (int i=0; i<m; ++i)
    {
        A[i] = new int[n]();
    }

    for (int i=0; i<m; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> A[i][j];
        }
    }

    cin >> p >> q;
    // allocate 2D array for matrix B
    B = new int*[p];
    for (int i=0; i<p; ++i)
    {
        B[i] = new int[q]();
    }

    for (int i=0; i<p; ++i)
    {
        for (int j=0; j<q; ++j)
        {
            cin >> B[i][j];
        }
    }

    int** R = MatrixMultiply(A, m, n, B, p, q);
    if (R == nullptr)
        cerr << "Cannot perform matrix operation" << endl;
    else
    {
        for (int i=0; i<m; ++i)
        {
            for (int j=0; j<q; ++j)
            {
                cout << R[i][j] << " ";
            }
            cout << endl;
        }
    }

    Delete2DDynamicArray(&A, m);
    Delete2DDynamicArray(&B, p);

    if (A == nullptr)
        cout << "A is null" << endl;
    // Note: be careful not to use !R in if statement as nullptr doesn't implicitly converted into
    // bool when using with ! alone.
    if (R != nullptr) Delete2DDynamicArray(&R, m);
    
    return 0;
}
 
