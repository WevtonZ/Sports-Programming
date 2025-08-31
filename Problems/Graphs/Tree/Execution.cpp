// https://codeforces.com/gym/106054/problem/E

#include "bits/stdc++.h"
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1 << (i)) & (x))
#define mp make_pair
#define mt make_tuple

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

struct LCA {
    int n, K; // quantidade de vértices do grafo / potências de 2 a serem consideradas.
    int timer; // temporizador para contar a entrada e saída de cada vértice.
    vector<vector<int>> & graph; // grafo referenciado para otimizar a velocidade.
    vector<int> dist; // distância entre dois vértices. Pode ser modificado.
    vector<int> in, out; // Tempo de entrada e saída de cada vértice.
    vector<vector<int>> st; // sparse table para calcular os pais em potencia de 2 de cada vertice

    // inicializar a struct de LCA com a qtd de vertices, o grafo e a raiz.
    // raiz padronizada como 1
    LCA(int n, vector<vector<int>> & graph, int root = 1) : n(n), graph(graph) {
        dist.resize(n+10,0);
        in.resize(n+10);
        out.resize(n+10);
        
        timer = 1;
        K = 0;
        while((1 << K) <= n) K++;
        
        // settando o tamanho da sparse table.
        st.resize(n+10);
        for(int i=0; i<=n; i++){
            st[i].resize(K+2);
        }
        build(root, root);
    }

    // criar as coisas
    void build(int u, int ant) {
        in[u] = timer++;
        st[u][0] = ant;
        for(int k=1; k<=K; k++){
            st[u][k] = st[st[u][k-1]][k-1];
        }

        for(int v: graph[u]){
            if(v == ant) continue;
            dist[v] = dist[u] + 1;
            build(v,u);
        }
        out[u] = timer++;
    }

    // u é ancestral de v?
    int is_ancestor(int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    }

    /*
    Funcao para calcular o LCA entre dois vértices.
    */
    int lca(int u, int v) {
        if(is_ancestor(u, v)) return u;
        if(is_ancestor(v, u)) return v;

        for(int i=K; i>=0; i--){
            if(!is_ancestor(st[u][i], v)){
                u = st[u][i];
            }
        }
        return st[u][0];
    }

    // função pra calcular a distância entre dois caras na árvore.
    // é possível só desaparecer com essa função se for necessário.
    int get_dist(int u, int v) {
        return dist[u] + dist[v] - 2*dist[lca(u,v)];
    }
};

void test() {
    /*
    O problema pode ser resolvido pensando da seguinte forma: todos os caras do mesmo nível serão usados para calcular a quantidade de pessoas que é possível matar antes delas chegarem
    no bunker. Então, podemos processar a árvore por nível, e a melhor forma de fazer isso é com um BFS.

    No BFS, processamos os filhos do nó 1, e em cada nível, somamos todo mundo desse nível para uma possível resposta. O turno em que isso é feito será o LCA de todos esses caras, e para
    calcular isso, podemos apenas pegar os LCAs em pares e o mais alto deles será o LCA de todos os caras do mesmo nível.
    */
  
    int n;
    cin >> n;

    vector<vector<int>> graph(n+1);

    vector<ll> a(n+1);
    for(int i=2; i<=n; i++) cin >> a[i];
    for(int i=1; i<n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    LCA d(n+1, graph); // montar o lca. magia

    vector<bool> vis(n+1, false);
    vis[1]=true;
    ll rs = 0, id = 1;
    for(auto k: graph[1]) {
        queue<pair<int,int>> q;
        q.push({k, 1});
        vis[k] = true;
        ll tmp = 0;
        int at = 1;
        vector<int> caras;

        while(!q.empty()) {
            auto [u, lvl] = q.front();
            q.pop();

            if(at == lvl) {
                tmp += a[u];
                if(a[u] > 0) caras.pb(u);
            }
            else{
                if(rs<tmp){
                    rs=tmp;
                    int t2 = 1;   

                    for(int i=0; i<int(caras.size())-1; i++){
                        int lc = d.lca(caras[i], caras[i+1]);
                        t2 = max(t2, max(d.dist[caras[i]], d.dist[caras[i+1]])-d.dist[lc]+1);
                    }
                    id=t2;
                }
                else if(rs == tmp) {
                    int t2=1;
                    for(int i=0; i<int(caras.size())-1; i++) {
                        // cout<<"entrei aqui"<<endl;
                        int lc = d.lca(caras[i], caras[i+1]);
                        t2 = max<ll>(t2, max(d.dist[caras[i]], d.dist[caras[i+1]])-d.dist[lc]+1);
                    }
                    id=min<ll>(id,t2);
                }
                at=lvl;
                tmp=a[u];
                caras.clear();
                if(a[u] > 0) caras.pb(u);
            }

            for(auto v: graph[u]) {
                if(vis[v]) continue;
                vis[v] = true;
                q.push({v, lvl+1});
            }
        }   

        if(rs < tmp) {
            rs=tmp;
            int t2 = 1;
            for(int i=0; i<int(caras.size())-1; i++){
                int lc = d.lca(caras[i], caras[i+1]);
                t2 = max(t2, max(d.dist[caras[i]], d.dist[caras[i+1]])-d.dist[lc]+1);
            }
            id=t2;
        }
        else if(rs == tmp) {
            int t2=1;
            for(int i=0; i<int(caras.size())-1; i++) {
                int lc = d.lca(caras[i], caras[i+1]);
                t2 = max<ll>(t2, max(d.dist[caras[i]], d.dist[caras[i+1]])-d.dist[lc]+1);
            }
            id=min<ll>(id,t2);
        }
    }

    cout << rs << " " << id << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);
    
    int tt=1;
    // cin >> tt;
    
    while(tt--){
        test();
    }
    
    return 0;
}
