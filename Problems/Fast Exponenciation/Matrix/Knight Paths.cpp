// https://codeforces.com/gym/102644/problem/E

#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(x, i) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

// ordenar antes de usar essa funcao
#define make_unique(x) x.erase(unique(x.begin(), x.end()), x.end())

using ll = long long;
using ld = long double;
using ull = unsigned int;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll mod = 1e9+7;
struct mi {
    int v;
    explicit operator int() const { return v; }
    mi(ll vv = 0) : v(vv % mod) { v += (v < 0) * mod; }
    friend mi& operator+=(mi& a,mi b){if((a.v += b.v) >= mod) a.v -= mod; return a;}
    friend mi& operator-=(mi& a,mi b){if((a.v -= b.v) < 0) a.v += mod; return a;}
    friend mi& operator*=(mi& a,mi b){a.v = 1ll*a.v*b.v%mod; return a;}
    friend mi& operator/=(mi& a,mi b){a *= inv(b); return a;}
    friend mi operator+(mi a,mi b){return a += b;}
    friend mi operator-(mi a,mi b){return a -= b;}
    friend mi operator*(mi a,mi b){return a *= b;}
    friend mi operator/(mi a,mi b){return a /= b;}
    friend mi fexp(mi a, ll b){
        mi ans = 1;
        while(b){
            if(b&1) ans *= a;
            b >>= 1;
            a *= a;
        }
        return ans;
    }
    friend mi inv(mi a){return fexp(a,mod-2);}
    friend ostream& operator<<(ostream& out, mi at){return out << at.v;}
    friend istream& operator>>(istream& in, mi &at){return in>>at.v;}
};

/*
  Indexada de 0
  Realiza soma e produto entre matrizes quadradas.
*/

const ll inf = 4e18;

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

void test() {
    int n;
    cin >> n;

    Matrix<ull> M(65), rs(65,true);
    vector<pair<int,int>> movs = {{2,1},{-2,1},{2,-1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2}};

    auto check = [&](int x, int y) {
        return x>=0 && y>=0 && x<8 && y<8;
    };

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            int u = i*8+j;
            for(auto [x,y]:movs){
                x+=i;
                y+=j;
                if(check(x,y)){
                    int v = x*8+y;
                    M[u][v]=1;
                }
            }
        }
    }
    for(int i=0; i<64; i++) M[i][64]=1;
    M[64][64]=1;
    n++;
    while(n){
        if(1&n) rs=rs*M;
        M=M*M;
        n>>=1;
    }

    cout<<rs[0][64]<<el;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
