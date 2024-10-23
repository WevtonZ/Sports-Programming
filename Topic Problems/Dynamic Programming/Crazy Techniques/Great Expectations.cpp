// https://codeforces.com/gym/103049/problem/G

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

struct peixe {
    int t, d;
    ld p;
};

int n, rr, m;
ld dp[55][50010];
peixe a[55];
int x;

/*
  Aqui temos um problema que, através de alguma abstração, vira uma DP em uma DAG. Temos um problema, que é que a DP cicla no [0,0], tornando inviável só codar a programação dinâmica.
  Para resolver isso, podemos fazer uma busca binária na resposta de DP[0,0]. Podemos fazer isso pois essa DP cicla apenas no [0,0], tornando viável buscarmos a resposta correta dele.
*/

void test() {
    cin >> n >> rr >> m;
    for(int i=0; i<m; i++) {
        cin >> a[i].t >> a[i].p >> a[i].d;
    }
    a[m].t = n;

    ld l, r;
    l = 0, r = 1e10;
    x=rr-n-1;
    for(int t=0; t<100; t++) {
        ld mid = (l + r) / 2.l;
        for(int i=0; i<=x; i++) {
            dp[m][i]=0;
        }
        for(int i=m-1; i>=0; i--) {
            for(int j=x; j>=0; j--) {
                int dist = a[i+1].t - a[i].t;
                ld val = mid;
                if(j+a[i].d <= x) val = min(val, a[i].d+dist+dp[i+1][j+a[i].d]);
                dp[i][j] = (a[i].p * (dist + dp[i+1][j])) + (1.l-a[i].p) * val;
            }
        }
        dp[0][0] += a[0].t;

        if(dp[0][0] <= mid)
            r = mid;
        else
            l = mid;
    }
    cout<<l<<"\n";
}   
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(10);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
