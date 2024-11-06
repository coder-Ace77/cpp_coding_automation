class Matrix {
public:
    vector<vector<ll>> mat;

    Matrix(){}

    Matrix(int n, int m) {
        mat.resize(n, vector<ll>(m)); 
    }

    Matrix(vector<vector<ll>> &v) {
        mat = v;
    }

    vector<ll>& operator[](int index) {
        return mat[index];
    }

    const vector<ll>& operator[](int index) const {
        return mat[index];
    }

    int rows() const {
        return mat.size();
    }

    int cols() const {
        return mat[0].size();
    }

    Matrix operator*(Matrix &x) {
        int n = mat.size();
        int m = mat[0].size();
        int p = x.mat[0].size();
        Matrix ans(n, p);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                ans.mat[i][j] = 0;
                for (int k = 0; k < m; k++) {
                    ans.mat[i][j] += (mat[i][k] * x.mat[k][j]);
                    // Apply modulo if needed
                }
            }
        }
        return ans;
    }

    Matrix iden(int n) {
        Matrix x(n, n);
        for (int i = 0; i < n; i++) x.mat[i][i] = 1;
        return x;
    }

    static Matrix binPow(Matrix &a, ll b) {
        int n = a.rows();
        if (b == 0) return a.iden(n);
        if (b % 2 == 1) {
            Matrix x = binPow(a, b / 2);
            return x * x * a;
        } else {
            Matrix x = binPow(a, b / 2);
            return x * x;
        }
    }

    // Transpose Function
    Matrix transpose() {
        int n = rows();
        int m = cols();
        Matrix transposed(m, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                transposed.mat[j][i] = mat[i][j];
            }
        }
        return transposed;
    }
};
