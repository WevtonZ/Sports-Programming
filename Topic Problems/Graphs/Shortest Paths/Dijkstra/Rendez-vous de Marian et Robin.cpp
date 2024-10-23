// https://codeforces.com/contest/2014/problem/E

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

const int N = 2e5+10;
const ll inf = 1e18;

vector<pair<int,ll>> e[N];

/*
  Um problema onde a gente quer fazer dois caras se encontrarem em um grafo direcionado, onde as arestas tem peso e tem uma forma de diminuir o peso de todas as arestas quando você
  chega em uma aresta específica. Clássico problema de Dijkstra, onde você faz seu vetor de distância ter mais uma linha, para poder calcular montado no cavalo ou não montado no cavalo.
  Após isso, só pegar o maior menor valor de todas as distâncias que você conseguiu alcançar.
*/

void test() {
    int n, m, h;
    cin >> n >> m >> h;
    set<int> S;
    
    for(int i=0; i<h; i++){
        int x; cin >> x;
        S.insert(x);
    }

    for(int i=0; i<m; i++){
        int x, y, z;
        cin >> x >> y >> z;
        e[x].pb({y,z});
        e[y].pb({x,z});
    }

    auto dij = [&](int s, vector<vector<ll>> & dist) {
        priority_queue<tuple<ll,int,bool>,vector<tuple<ll,int,bool>>,greater<>> q;
        bool ok2 = S.find(s) != S.end();
        q.push(mt(0,s,ok2));


        dist.assign(n+1, vector<ll>(2, inf));
        dist[s][ok2] = 0;

        while(!q.empty()){
            auto [d, u, ok] = q.top();
            q.pop();

            if(dist[u][ok] != d) continue;
            ok2 = (ok | (S.find(u) != S.end()));
            for(auto [v, w]: e[u]) {
                ll tmp;
                if(ok2) tmp = d + w/2;
                else tmp = d + w;
                if(tmp < dist[v][ok2]){
                    dist[v][ok2] = tmp;
                    q.push(mt(tmp, v, ok2));
                }
            }
        }
    };

    vector<vector<ll>> d1, d2;
    dij(1, d1);
    if(d1[n][0] == inf && d1[n][1] == inf){
        cout<<"-1\n";
        for(int i=1; i<=n; i++){
            e[i].clear();
        }
        return;
    }
    dij(n, d2);

    ll rs = inf;
    for(int i=1; i<=n; i++) {
        rs = min(rs, max({min(d1[i][0], d1[i][1]), min(d2[i][0], d2[i][1])}));
    }
    cout<<rs<<"\n";

    
    for(int i=1; i<=n; i++){
        e[i].clear();
    }
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
 
    int t = 1;
    cin >> t;
    // cout<<"\n";
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
