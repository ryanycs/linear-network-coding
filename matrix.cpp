#include "matrix.h"

vector<vector<int>> mat_inverse(vector<vector<int>> &mat) {
    int n = mat.size();
    vector<vector<int>> a(n, vector<int>(n * 2)), res(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = mat[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                a[i][j+n] = 1;
            }
        }
    }

    // Gauss Jordan Elimination
    for (int i = 0; i < n; ++i) {
        int pivot_row = -1;

        // Find the first row with a non-zero element in column i
        for (int j = i; j < n; ++j) {
            if (a[j][i] == 1) {
                pivot_row = j;
                break;
            }
        }

        // Swap rows
        swap(a[i], a[pivot_row]);

        // Perform row operations to make all other elements in the column zero
        for (int j = 0; j < n; ++j) {
            // row_j = row_j - row_i
            if (i != j && a[j][i] == 1) {
                for (int k = 0; k < 2 * n; ++k) {
                    a[j][k] ^= a[i][k];
                }
            }
        }
    }

    // Copy the result
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = a[i][j+n];
        }
    }

    return res;
}

vector<vector<int>> mat_mul(vector<vector<int>> &mat_1, vector<vector<int>> &mat_2) {
    int r1 = mat_1.size(), c1 = mat_1[0].size(), c2 = mat_2[0].size();
    vector<vector<int>> res(r1, vector<int>(c2));

    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            for (int k = 0; k < c1; ++k) {
                res[i][j] ^= mat_1[i][k] & mat_2[k][j];
            }
        }
    }

    return res;
}

vector<vector<int>> generate_indep_mat(int n) {
    int round = rand() % (n * 5);
    vector<vector<int>> res(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }

    // row operations
    for (int i = 0; i < round; ++i) {
        int row_a, row_b, op;

        op = rand() % 3;
        switch(op) {
            case 0:
                // Multiply a nonzero constant. In GF(2), it's do nothing
                break;
            case 1:
                // Interchange two rows
                row_a = rand() % n;
                row_b = rand() % n;
                swap(res[row_a], res[row_b]);
                break;
            case 2:
                // Add one row to another
                row_a = rand() % n;
                do row_b = rand() % n; while (row_b == row_a);
                for (int j = 0; j < n; ++j) {
                    res[row_a][j] = res[row_a][j] ^ res[row_b][j];
                }
                break;
            default:
                break;
        }
    }

    return res;
}