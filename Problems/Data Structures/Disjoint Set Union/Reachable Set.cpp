// https://atcoder.jp/contests/abc401/tasks/abc401_e

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
 
template <typename T, typename T1> ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}

template <typename T, typename T1> istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const int MOD = 1e9+7;

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

const int N = 2e5+10;

/*
    Simple algorithm for Disjoint Set Union Data Structure. Uses Union by Size instead of rank because they are
    almost the same complexity. Uses path compression heuristic.
    
    1 indexed.
*/

struct DSU {
    vector<int> pai, sz; // pai e quantidade que ele guarda.
    int n; // quantidade de vértices no meu DSU.

    DSU(int n) : n(n) {
        pai.resize(n+10);
        sz.assign(n+10, 1);
        for(int i=0; i<=n; i++){
            pai[i]=i;
        }
    }

    // procura o representante desse cara. Usa compressão de caminhos.
    int find(int x) {
        if(x == pai[x]) return x;
        return pai[x] = find(pai[x]);
    }

    // une os conjuntos entre dois caras. Usa união por tamanho.
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

vector<int> graph[N];

void test(){
    /*
        Para esse problema, podemos manter uma DSU para saber se os vértices que queremos, ordenados, estao ligados.
        Para isso, manteremos a lista de adjacência do grafo e manteremos algumas variaveis auxiliares para ajudar com o problema.
        Contaremos a quantidade de componentes do grafo. Se for diferente de 1, então nem todos os vértices que importam
        pra mim estão conectados, assim, imprimimos -1. Caso contrário, contamos quantos dos outros vértices que nao queremos
        vamos deletar, e imprimimos essa quantidade.
    */
    int n, m;
    cin >> n >> m;

    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    DSU dsu(n);

    vector<bool> vis(n+1, false);
    int cc=0, er=0;

    for(int u=1; u<=n; u++) {
        cc++;

        if(vis[u]) er--;
        for(auto v: graph[u]) {
            if(v < u) {
                if(dsu.unite(u, v)) {
                    cc--;
                }
            }
            else {
                if(!vis[v]) er++;
                vis[v] = true;
            }
        }

        if(cc == 1) {
            cout << er << "\n";
        }
        else {
            cout << "-1\n";
        }
    }
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(10);
    
    int tt = 1;
    // cin >> tt;
 
    for(int i=1; i<=tt; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
