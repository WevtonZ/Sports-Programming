/*
  Indexada de 0
  Realiza soma e produto entre matrizes quadradas. Não pretendo expandir para matrizes genéricas
*/

template<class T> struct Matrix {
    vector<vector<T>> mat;
    int n;
    Matrix() {}
    Matrix(int _n, bool id = false) : n(_n) {
        mat.assign(n,vector<T>(n,0));
        if(id){
            for(int i=0; i<n; i++){
                mat[i][i]=1;
            }
        }
    }
    Matrix(vector<vector<T>> & M) : mat(M), n(M.size()) {}

    vector<T> & operator[](int i) { return mat[i]; }
    const vector<T>& operator[](int i) const { return mat[i]; }

    Matrix operator+(const Matrix & o) const {
        Matrix res(n);
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) res[i][j]=mat[i][j]+o[i][j];
        return res;
    }

    Matrix operator*(const Matrix & o) const {
        Matrix res(n);
        for(int i=0; i<n; i++) for(int k=0; k<n; k++){
            for(int j=0; j<n; j++){
                res[i][j]+=mat[i][k]*o[k][j];
            }
        }
        return res;
    }
};
