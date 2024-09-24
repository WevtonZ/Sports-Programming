// https://codeforces.com/contest/2014/problem/H

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

#pragma endregion

const int N = 1e6+10;

int mark[N];
vector<int> a;

struct query{
    static const int K = 350;
    int l, r, idx;

    query(int l, int r, int idx) {
        this->l = l;
        this->r = r;
        this->idx = idx;
    }

    bool operator <(const query &o){
        if(l/K == o.l/K){
            if((l/K)&1){
                return r > o.r;
            }
            return r<o.r;
        }
        return l/K<o.l/K;
    }
};

struct MO{
    vector<query> queries;
    vector<bool> rs;
    int ct = 0; // saber quantos caras impares tem no meu vetor de marcação.

    MO(vector<query> queries){
        this->queries = queries;
    }

    void add(int x){
        mark[x]++;
        if((mark[x]&1)) ct++;
        else ct--;
    }

    void rmv(int x){
        mark[x]--;
        if((mark[x]&1)) ct++;
        else ct--;
    }

    int calc(){
        return ct == 0;
    }

    void solve(){
        sort(all(queries));
        rs.resize(queries.size());

        int i = 0, j = -1;
        for(auto [l, r, idx]: queries){
            while(j < r){
                j++;
                add(a[j]);
            }

            while(j > r){
                rmv(a[j]);
                j--;
            }

            while(i > l){
                i--;
                add(a[i]);
            }

            while(i < l){
                rmv(a[i]);
                i++;
            }

            rs[idx]=calc();
        }
    }
};


void test() {
    int n, q;
    cin >> n >> q;
    a.assign(n, 0);
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    vector<query> queries;
    for(int i=0; i<q; i++){
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries.eb(l, r, i);
    }

    MO mo(queries);
    mo.solve();
    for(int i=0; i<q; i++){
        cout << (mo.rs[i] ? "YES" : "NO") <<"\n";
    }
    for(int i=0; i<n; i++){
        mark[a[i]]=0;
    }
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);

    int t = 1;
    cin >> t;

    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
