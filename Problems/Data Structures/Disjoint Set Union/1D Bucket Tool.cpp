// https://atcoder.jp/contests/abc380/tasks/abc380_e

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

struct DSU {
    int n;

    vector<int> pai, sz;

    DSU(int n) {
        this->n = n;
        pai.resize(n);
        sz.assign(n, 1);
        for(int i=0; i<n; i++){
            pai[i]=i;
            sz[i] = 1;
        }
    }

    int size(int x) {
        return sz[find(x)];
    }

    int find(int x) {
        if(x == pai[x]) return x;
        return pai[x] = find(pai[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(a > b) swap(a,b);
        pai[b]=a;
        sz[a]+=sz[b];

        return true;
    }
};

void test() {
    int n, q;
    cin >> n >> q;
    vector<int> rs, cor;
    rs.resize(n+1, 1);
    cor.resize(n+1);
    for(int i=1; i<=n; i++) cor[i]=i;

    DSU dsu(n+1);

    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, c;
            cin >> x >> c;
            
            int l = dsu.find(x);
            int r = l+dsu.size(x);
            
            rs[cor[l]]-=r-l;
            rs[c]+=r-l;  
            cor[l]=c;

            while(l) {
                if(cor[dsu.find(l-1)] != c) break;
                dsu.unite(l, l-1);
                l = dsu.find(l);
            }
            while(r <= n) {
                if(cor[dsu.find(r)] != c) break;
                dsu.unite(r,r-1);
                r = dsu.find(l) + dsu.size(l);
            }
        }
        else{
            int c;
            cin >> c;
            cout << rs[c] << "\n";
        }
    }
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
