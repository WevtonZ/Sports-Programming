// https://cses.fi/problemset/task/2208/

#include <bits/stdc++.h>
using namespace std;
 
#pragma region
 
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define eb emplace_back
#define pb push_back
#define get_bit(x,i) ((x)&(1ll<<(i)))
 
using ll = long long;
using ld = long double;
// using i128 = __int128_t;
 
// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
 
const int MOD = 998244353;
 
struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD;}
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
 
void test(){
    int n;
    cin >> n;
 
    bool ok=false;
    for(int i=0; i<n; i++){
        int x; cin >> x;
        if(x%2) ok=true;
    }
    cout<<(ok?"first\n":"second\n");
}
 
int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(15);
    
    int tt = 1;
    cin >> tt;
 
    for(int i=1; i<=tt; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
