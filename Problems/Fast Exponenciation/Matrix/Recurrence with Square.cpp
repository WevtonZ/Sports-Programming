// https://codeforces.com/gym/102644/problem/G

#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(i, x) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

// ordenar antes de usar essa funcao
#define make_unique(x) x.erase(unique(x.begin(), x.end()), x.end())

using ll = long long;
using ld = long double;

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
 
    Matrix operator*(const Matrix & o) const {
        Matrix res(n);
        for(int i=0; i<n; i++) for(int k=0; k<n; k++){
            for(int j=0; j<n; j++){
                res[i][j]+=mat[i][k]*o[k][j];
            }
        }
        return res;
    }
 
    vector<T> operator*(const vector<T> & o) const {
        vector<T> res(n);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                res[i]+=mat[i][j]*o[j];
            }
        }
        return res;
    }
};

void test() {
    int n;
    ll k;
    cin >> n >> k;

    Matrix<mi> M(n+3), tmp(n+3, true);
    vector<mi> a;
    for(int i=0; i<n; i++) {
        int x; cin >> x;
        a.push_back(x);
        if(i+1<n) M[i+1][i]=1;
    }
    if(k<n){
        cout<<a[k]<<el;
        return;
    }   
    reverse(all(a));
    for(int i=0; i<n; i++){
        int c; cin >> c;
        M[0][i]=c;
    }
    int p, q, r;
    cin >> p >> q >> r;

    a.push_back(n*n);
    a.push_back(n);
    a.push_back(1);
    
    M[0][n]=r, M[0][n+1]=q, M[0][n+2]=p;
    M[n][n]=1;
    M[n][n+1]=2;
    M[n][n+2]=1;
    M[n+1][n+1]=M[n+1][n+2]=1;
    M[n+2][n+2]=1;

    // for(int i=0; i<n+3; i++){
    //     for(int j=0; j<n+3; j++){
    //         cout<<M[i][j]<<" ";
    //     }
    //     cout<<el;
    // }
    // cout<<el;

    k-=n-1;
    while(k){
        if(1ll&k) tmp=tmp*M;
        M=M*M;
        k>>=1ll;
    }
    // for(int i=0; i<n+3; i++){
    //     for(int j=0; j<n+3; j++){
    //         cout<<tmp[i][j]<<" ";
    //     }
    //     cout<<el;
    // }
    // cout<<el;
    auto rs = tmp*a;
    // auto rs = a*tmp;
    // for(auto i: a) cout<<i<<" ";
    // cout<<el;
    // for(auto i: rs) cout<<i<<" ";
    // cout<<el;
    cout<<rs[0]<<el;
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(6);
 
    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
