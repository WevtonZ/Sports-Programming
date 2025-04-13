// https://codeforces.com/group/btcK4I5D5f/contest/346791/problem/D

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
#define eb emplace_back
#define pb push_back
 
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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#pragma endregion

const int N = 2e5+10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
vector<pair<int,ll>> graph[N];

void test(){
    /*
      Problema clássico de Dijkstra, onde você tem uma posição inicial, quer chegar em um ou mais pontos com a distância mínima e pode dividir uma das distâncias uma vez por 2.
      Acontece que esse problema é facilmente resolvido usando o algoritmo de Dijkstra, onde podemos manter dois estados:

        dp[u,0]: Distância mínima para alcançar o vértice u, sem usar a divisão;
        dp[u,1]: Distância mínima para alcançar o vértice u, usando a divisão.

        Com isso, temos as seguintes transições:

        dp[v,0] = min(dp[v,0], dp[u,0]+w), onde u é o vértice atual, v é um vizinho de u que ainda não foi visitado e w é o peso da aresta entre eles.
        dp[v,1] = min(dp[v,1], dp[u,0]+w/2);
        dp[v,1] = min(dp[v,1], dp[u,1]+w).

        Após rodarmos o algoritmo, temos, para cada estado de dp[i,j], os caminhos mínimos a partir de algum ponto x qualquer selecionado. Assim, podemos resolver o problema. 
    */
  
    int n, m;
    cin >> n >> m;

    for(int i=0; i<m; i++){
        int a, b;
        ll c;
        cin >> a >> b >> c;
        graph[a].pb({b,c});
        graph[b].pb({a,c});
    }

    int k;
    cin >> k;
    vector<int> rota;
    for(int i=0; i<k; i++){
        int x;
        cin>>x;
        rota.pb(x);
    }

    vector<ll> d(n+1, inf);
    d[rota[0]]=d[rota[1]]=0;
    for(int i=2; i<k; i++){
        for(auto [v, w]: graph[rota[i-1]]){
            if(v==rota[i]){
                if(d[rota[i]] - (d[rota[i-1]]+w) > 0){
                    d[rota[i]]=d[rota[i-1]]+w;
                }
            }
        }
    }

    vector<vector<ll>> dist(n+1, vector<ll>(2, inf));
    vector<vector<pair<int,int>>> par(n+1, vector<pair<int,int>>(2));
    for(int i=1; i<=n; i++){
        for(int j=0; j<2; j++) par[i][j]={-1,-1};
    }

    dist[1][0] = dist[1][1] = 0;
    min_priority_queue<tuple<ll,int,int>> q;
    q.push({0.0l, 1, 0});

    while(!q.empty()) {
        auto [w, u, flag] = q.top();
        q.pop();
        if(dist[u][flag] != w) continue;

        if(flag == 0) {
            for(auto [v, ww]: graph[u]) {
                ll tmp = ww+w;
                if(dist[v][flag]>tmp){
                    dist[v][flag]=tmp;
                    par[v][flag]={u,flag};
                    q.push({tmp,v,flag});
                }
                tmp=ww/2+w;
                if(dist[v][1]>tmp){
                    dist[v][1]=tmp;
                    par[v][1]={u,flag};
                    q.push({tmp,v,1});
                }
            }
        }
        if(flag == 1) {
            for(auto [v, ww]: graph[u]) {
                ll tmp = ww+w;
                if(dist[v][flag]>tmp){
                    dist[v][flag]=tmp;
                    par[v][flag]={u,flag};
                    q.push({tmp,v,flag});
                }
            }
        }
    }

    for(int i=1; i<k-1; i++){
        int p=rota[i];
        for(int j=0; j<2; j++){
            if(d[p]-dist[p][j]>0){
                cout<<"Sim\n";

                vector<pair<int,int>> path;

                while(p!=-1 && j!=-1){
                    path.pb({p,j});
                    tie(p,j)=par[p][j];
                }

                reverse(all(path));
                cout<<path.size()<<"\n";
                cout<<path[0].ft;
                for(int v=1; v<path.size(); v++){
                    if(path[v-1].sd == 0 && path[v].sd == 1) cout<<" => ";
                    else cout<<" -> ";
                    cout<<path[v].ft;
                }
                cout<<"\n";

                return;
            }
        }
    }

    cout<<"Nao\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(15);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
