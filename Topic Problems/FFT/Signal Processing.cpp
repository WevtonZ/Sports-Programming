#include <bits/stdc++.h>
using namespace std;
 
#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
 
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdb = pair<ld,ld>;
 
// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T, typename T1>
ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1>
istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}
 
const int MOD = 1e9 + 7;
 
struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi &operator+=(mi &a, mi b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
mi &operator-=(mi &a, mi b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v * b.v); }
mi &operator*=(mi &a, mi b) { return a = a * b; }
mi mypow(mi a, long long p) {
    assert(p >= 0);
    return p == 0 ? 1 : mypow(a * a, p / 2) * (p & 1 ? a : 1);
}
mi inv(mi a) {
    assert(a.v != 0);
    return mypow(a, MOD - 2);
}
mi operator/(mi a, mi b) { return a * inv(b); }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion
 
using cd = complex<double>;
const double PI = acos(-1);
 
void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    for(int i=1, j=0; i < n; i++) {
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) 
            j^=bit;
        j^=bit;
 
        if(i < j) swap(a[i], a[j]);
    }
 
    for(int len = 2; len <= n; len <<= 1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i+=len) {
            cd w(1);
            for(int j=0; j<len/2; j++) {
                cd u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w*=wlen;
            }
        }
    }
 
    if(invert) {
        for(cd & x: a) {
            x /= n;
        }
    }
}
 
vector<int> multiply(vector<int> const &a, vector<int> const &b) {
    vector<cd> fa(all(a)), fb(all(b));
    int n = 1;
    while(n < a.size() + b.size()) n<<=1;
    fa.resize(n);
    fb.resize(n);
 
    fft(fa, false);
    fft(fb, false);
    for(int i=0; i<n; i++) 
        fa[i] *= fb[i];
    fft(fa, true);
 
    vector<int> result(n);
    for(int i=0; i<n;i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}
 
void test() {
    /*
        Problema que envolve interpretar os dois vetores como dois polinômios e fazer a multiplicação deles.
        A ideia é basicamente inverter o segundo polinômio. Se você inverte ele, o problema vira um problema básico de multiplicação de
        polinômios. Pode ser usado Karatsuba ou FFT pra resolver o problema. Aqui está uma implementação usando FFT.

        No final vai ter alguns caras que são zero que precisam ser removidos. Aí é só remover.
    */
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(auto &i: a) cin >> i;
    for(auto &i: b) cin >> i;
    reverse(all(b));
    vector<int> ans = multiply(a, b);
    while(ans.back() == 0) ans.pop_back();
    for(auto i: ans) cout<<i<<" ";
    cout<<"\n";
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(1);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
