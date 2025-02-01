#include <bits/stdc++.h>
using namespace std;

#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
typedef vector<int> vi;
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
using i128 = __int128_t;

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int N = 2e5+10;
const int K = 25;
const int INF = 1e9;

vector<vector<int>> graph;
vector<int> in, out, dist;
vector<vector<int>> st;
int cc;
int pai[N], cor[N];

// fazer todos os cálculos de LCA necessários.
void dfs_lca(int x, int p) {
    st[x][0]=p;
    for(int i=1; i<=K; i++){
        st[x][i]=st[st[x][i-1]][i-1];
    }
    in[x]=cc++;
    for(auto i: graph[x]){
        if(i != p) {
            dist[i] = dist[x] + 1;
            dfs_lca(i, x);
        }
    }
    out[x]=cc++;
}

// função para inicializar o LCA de todos os caras.
void lca_init(int n) {
    in.resize(n);
    out.resize(n);
    dist.assign(n, 0);
    st.resize(n);
    for(int i=0; i<n; i++){
        st[i].resize(K+1, 0);
    }
    cc = 1;
    dist[1]=0;
    dfs_lca(1,1);
}

// u é ancestral de v?
bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

// achar o LCA entre dois vértices.
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

int get_dist(int u, int v) {
    return dist[u] + dist[v] - 2*dist[lca(u,v)];
}

/*
    Indexado de 1
*/
struct Centroid{
    vector<int> p; // o pai de cada cara no centroide
    vector<bool> vis; // visitado para construir o centroide
    vector<int> tam; // tam da subarvore
    vector<vector<int>> & graph; // referencia da arvore original
    vector<int> best; // melhores distancias.
    int n; // qtd de vertices 
    int r; // raiz do centroide

    // grafo como referência!
    Centroid(int n, vector<vector<int>> & graph) : graph(graph), n(n){
        tam.resize(n+10);
        vis.resize(n+10);
        best.assign(n+10, 1e9);
        // qtd.resize(n+10);
        p.resize(n+10);
        r=build(1);
    }

    // constroi o centroid decomposition
    int build(int u){
        set_tam(u,u);
        u = find_centroid(u);
        vis[u]=1;

        p[u]=u;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            int x=build(v);
            p[x]=u;
        }    
        return u;
    }

    // ajusta os tamanhos das subárvores.
    void set_tam(int u,int ant){
        tam[u]=1;
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            set_tam(v,u);
            tam[u]+=tam[v];
        }
    }
    int find_centroid(int u){
        while(1){
            int flag=1;
            for(auto v: graph[u]){
                if(vis[v]) continue;
                if(tam[v]*2 > tam[u]){
                    tam[u]-=tam[v];
                    tam[v]+=tam[u];
                    u=v;
                    flag=0;
                    break;
                }
            }
            if(flag) break;
        }
        return u;
    }

    void update(int u,int ant){
        best[u]=0;
        int x = u;
        while(u!=p[u]){
            u = p[u];
            best[u] = min(best[u], get_dist(u, x));
        }
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            update(v,u);
        }
    }

    int query(int u, int ant) {
        int rs = best[u];
        int x = u;
        while(u!=p[u]){
            u=p[u];
            rs = min(rs, best[u]+get_dist(u,x));
        }
        return rs;
    }
};

void test() {
    /*
    Problema relacionado a Centroid Decomposition.
    Inicialmente, vamos receber uma árvore qualquer e queremos responder algum tipo de query sobre essa árvore. As
    queries geralmente são coisas relacionadas a caminhos em uma árvore, e queremos conseguir resolver essas queries rápido.
    O grande problema de tudo isso é que é meio lento de resolver problemas em caminhos se os caminhos forem muito profundos.
    As queries são a seguinte para esse problema:
        1: Pintar um cara de uma cor;
        2: Responder qual o nó pintado mais próximo de um cara u que eu escolher.
    
    Vamos enraizar a árvore em qualquer cara, o 1 por exemplo, e agora vamos tentar resolver as queries. Ignorando a
    complexidade, podemos fazer o seguinte:
    
    * Para resolver a query do tipo 1, podemos só colocar a distância desse cara como 0, e calcular a distância desse cara
    até a raiz da árvore, e atualizando os nós intermediários com a menor distância que eles encontraram no caminho. A
    complexidade de fazer isso é O(K), onde K é o tamanho do caminho até a raiz.

    * Para resolver a query do tipo 2, podemos usar o algoritmo de LCA para calcular a distância do nó que queremos para
    o nó mais próximo que está pintado na árvore. Essa query fica O(K log N), onde K é o tamanho do caminho até a raiz
    e o log N vem do algoritmo de LCA.

    Com isso a gente consegue resolver o problema em complexidade O(N*sum(K)*logN). O negócio é que K pode ir até N,
    resultando em um algoritmo O(N²logN), o que seria um problema para N = 10⁵.

    Se pudéssemos fazer com que a árvore seja balanceada, ou seja, tenha profundidade no máximo O(logN), poderíamos resolver
    as queries de forma bem eficiente, e fazendo exatamente as mesmas coisas. E é isso que Centroid Decomposition faz!

    Vamos seguir os seguintes passos para montar a nossa árvore:
    
        Criamos uma nova árvore usando um nó especial que chamamos de Centroide da árvore. Esse cara limita o tamanho
        da subárvore em no máximo N/2 vértices, e isso é interessante pois faz a gente ser capaz de criar uma árvore
        mais balanceada, que contém O(log N) de profundidade, assim ocasionando em updates e queries eficientes em árvores,
        quando o problema se trata de resolver coisas em caminhos.
    
    Com isso, podemos garantir a profundidade da árvore de ser Log N e assim podemos realizar as mesmas operações ditas
    acima em uma complexidade bem mais em conta. O(NlogN + Qlog²N) = O(Qlog²N)
    
    */
    int n, q;
    cin >> n >> q;
    graph.resize(n+1);
    for(int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }

    lca_init(n+1);
    Centroid cent(n, graph);
    cent.update(1, 1);

    for(int i=0; i<q; i++){
        int t, x;
        cin >> t >> x;
        if(t == 1) {
            cent.update(x, x);
        }
        else{
            cout << cent.query(x, x) << "\n";
        }
    }
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
