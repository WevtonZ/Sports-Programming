// https://codeforces.com/problemset/problem/1461/C

/*
    Basicamente não estamos interessados em ordenar os valores que estão antes do último valor na posição errada. Agora o que resta é experimentos que podem deixar o vetor
    ordenado de cara. A ideia é que, se você quer que o experimento atual funcione, todos os outros experimentos válidos que vieram anteriormente devem ter falhado. Assim,
    podemos só manter ambas coisas: um prefixo de experimentos falhos e uma variável que vai somar todos esses valores.
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
    int n, m;
    cin >> n >> m;
    ld rs = 0;
    vector<int> a(n);
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    int id=0;
    for(int i=0; i<n; i++){
        if(a[i]-1 != i) id = i+1;
    }
    vector<pair<int,ld>> b(m);
    for(int i=0; i<m; i++) {
        cin >> b[i];
    }
    if(id == 0){
        cout<<1.0<<"\n";
        return;
    }
    ld tmp = 1;
    for(int i=0; i<m; i++){
        auto [x, v] = b[i];
        if(x >= id){
            rs += tmp*v;
            tmp *= (1-v);
        }
    }
    cout << rs << "\n";
} 
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(15);
 
    int t = 1;
    cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
