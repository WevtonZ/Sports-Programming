// https://judge.beecrowd.com/pt/problems/view/3057

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

const int N = 1e3+10;

vector<int> e[N];
vector<bool> vis;

set<int> S;
set<int> T[N];
vector<int> in, I0;

void dfs(int x, int id) {
    vis[x]=true;
    T[x].insert(id);
    for(auto i: e[x]) {
        if(!vis[i]){
            dfs(i, id);
        }
    }
}

void dfs(int x) {
    vis[x]=true;
    S.insert(x);
    for(auto i: e[x]){
        if(!vis[i]) dfs(i);
    }
}

void test() {
    /*
        Vamos primeiro definir, para cada vértice, quem são os vértices que chegam nele na ordem topológica (apenas aqueles com
        grau 0 de entrada). Com essa informação, e com a informação inicial dos vértices descobertos, todos os vértices que
        contém esse mesmo conjunto de vértices, ou são um superset do conjunto que estamos olhando agora, devem estar também
        na resposta. A motivação é simples, eles possuem os mesmos vértices que poderiam ter ativado eles, logo ambos estão
        descobertos, mesmo que não saibamos quem entre os vértices ativou eles.
    */

    int n, m, v;
    cin >> n >> m >> v;
    in.assign(n+1, 0);
    for(int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        e[x].pb(y);
        in[y]++;
    }

    for(int i=1; i<=n; i++){
        if(in[i]==0) I0.pb(i);
    }

    for(auto i: I0) {
        vis.assign(n+1, false);
        dfs(i, i);
    }

    for(int i=0; i<v; i++) {
        int x;
        cin >> x;
        S.insert(x);
        for(int j=1; j<=n; j++) {
            bool ok=true;
            for(auto k: T[x]) {
                if(T[j].count(k) == 0) {
                    ok=false;
                }
            }
            if(ok) S.insert(j);
        }
    }

    vector<int> a(all(S));

    for(auto i: a){
        dfs(i);
    }

    vector<int> rs(all(S));
    for(int i=0; i<rs.size(); i++){
        cout<<rs[i];
        if(i+1<rs.size()) cout<<" ";
    }
    cout<<"\n";
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
