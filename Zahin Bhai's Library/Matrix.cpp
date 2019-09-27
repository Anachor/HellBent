#include <bits/stdtr1c++.h>

#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct Matrix{
    int row, col;
    int ar[101][101]; /// Change matrix size here, also change to long long for safety

    Matrix(){} ///Beware if matrix can contain negative numbers in matrix exponentiation problems
    Matrix(int n, int m, int diagonal = 0){
        clr(ar);
        row = n, col = m;
        for (int i = min(n, m) - 1; i >= 0; i--) ar[i][i] = diagonal;
    }

    /// To multiply two matrices A and B, the number of columns in A must equal the number of rows in B
    Matrix operator* (const Matrix& other) const{ /// hash = 709758
        int i, j, k;
		Matrix res(row, other.col);
		long long x, y = (long long)MOD * MOD;

		for(i = 0; i < row; i++){
			for(j = 0; j < other.col; j++){
				for(k = 0, x = 0; k < col; k++){
					x += ((long long)ar[i][k] * other.ar[k][j]); /// replace matrix other with its transpose matrix to reduce cache miss
					if (x >= y) x -= y;
				}
				res.ar[i][j] = x % MOD;
			}
		}
		return res;
	}

	Matrix operator^ (long long n) const{
	    Matrix x = *this, res = Matrix(row, col, 1);
		while (n){
			if (n & 1) res = res * x;
			n = n >> 1, x = x * x;
		}
		return res;
	}

    /// Transpose matrix, T[i][j] = ar[j][i]
	Matrix transpose(){
	    Matrix res = Matrix(col, row);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                res.ar[j][i] = ar[i][j];
            }
        }
        return res;
	}

	/// rotates the matrix 90 degrees clockwise
	Matrix rotate(){
        Matrix res = this->transpose();
        for (int i = 0; i < res.row; i++) reverse(res.ar[i], res.ar[i] + res.col);
        return res;
	}

	inline void print(){
	    for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                printf("%d%c", ar[i][j], ((j + 1) == col) ? 10 : 32);
            }
	    }
	}
};

int main(){
    Matrix a = Matrix(4, 5, 1);
    int k = 0;
    for (int i = 0; i < a.row; i++){
        for (int j = 0; j < a.col; j++){
            a.ar[i][j] = ++k;
        }
    }
    a.print();
    puts("");
    Matrix b = a.rotate();
    b.print();
    return 0;

    Matrix x = Matrix(5, 5, 5);
    Matrix y = x ^ 5;
    x.print();
    y.print();
}


/***

Sometimes we may need to maintain more than one recurrence, where they are interrelated.
For example, let a recurrence relation be:
g(n) = 2g(n-1) + 2g(n-2) + f(n), where, f(n) = 2f(n-1) + 2f(n-2).
Here, recurrence g(n) is dependent upon f(n) and the can be calculated in the same matrix
but of increased dimensions. Lets design the matrices A, B then we'll try to find matrix M.


                        Matrix A	            Matrix B

                        |  g(n)  |              | g(n+1) |
                        | g(n-1) |              |  g(n)  |
                        | f(n+1) |              | f(n+2) |
                        |  f(n)  |              | f(n+1) |


Here, g(n+1) = 2g(n) + 2g(n-1) + f(n+1) and f(n+2) = 2f(n+1) + 2f(n).
Now, using the above process, we can generate the objective matrix M as follows:

| 2  2  1  0 |
| 1  0  0  0 |
| 0  0  2  2 |
| 0  0  1  0 |


/// Matrix Rotations:

Rotate by +90:
Transpose
Reverse each row

Rotate by -90:
Transpose
Reverse each column


Rotate by +180:
Method 1: Rotate by +90 twice
Method 2: Reverse each row and then reverse each column

Rotate by -180:
Method 1: Rotate by -90 twice
Method 2: Reverse each column and then reverse each row
Method 3: Reverse by +180 as they are same

***/
