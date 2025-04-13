// https://judge.beecrowd.com/pt/problems/view/2459

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
using ull = uint64_t;
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

struct Edge {
    int u, v, w;

    Edge(int _u, int _v, int _w) {
        this->u= _u;
        this->v= _v;
        this->w= _w;
    }

    bool operator<(const Edge &o) {
        return w < o.w;
    }
};

struct DSU {
    vector<int> pai, sz;
    int n;

    DSU(int n) {
        this->n = n;
        pai.resize(n);
        sz.assign(n, 1);
        for(int i=0; i<n; i++){
            pai[i]=i;
        }
    }

    int find(int x) {
        if(x == pai[x]) return x;
        return pai[x] = find(pai[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a,b);
        sz[a]+=b;
        pai[b]=a;
        return true;
    }
};

void test() {
    // um problema simples. Faz o DSU primeiro nas ferrovias e depois nas rodovias.
  
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> a, b;
    for(int i=0; i<m; i++){
        int u,v,w;
        cin>>u>>v>>w;
        a.eb(u,v,w);
    }

    for(int i=0; i<k; i++){
        int u,v,w;
        cin>>u>>v>>w;
        b.eb(u,v,w);
    }

    sort(all(a));
    sort(all(b));

    DSU dsu(n+1);
    int rs=0;
    for(auto [u,v,w]: a) {
        if(dsu.unite(u,v)){
            rs+=w;
        }
    }
    for(auto [u,v,w]: b) {
        if(dsu.unite(u,v)){
            rs+=w;
        }
    }

    cout<<rs<<"\n";
}   
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
