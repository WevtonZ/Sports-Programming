// https://codeforces.com/contest/453/problem/A

/*
    Se fosse somente uma rolagem, teríamos X/N - (X-1)/N, onde X é o valor da face que queremos calcular, e N é a quantidade total de faces.
    Para uma fórmula geral, faremos o somatório de X variando de 1 até N, e somaremos X * ((X/N)^K - ((X-1)/N)^K), onde K é o número de rolagens que serão feitas.
*/

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
 
#define rep(i, begin, end) for(__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2*((begin) > (end)))
 
// using i128 = __int128_t;
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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MOD = 1e9+7;
 
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
 
#pragma endregion


void test() {
    ld rs = 0; // resposta

    int m, n;
    cin >> m >> n;

    for(int x=1; x<=m; x++) {
        rs += (ld(x) * (pow(ld(x)/m, n) - pow(ld(x-1)/m, n)));
    }
    cout<<rs<<"\n";
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(15);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
