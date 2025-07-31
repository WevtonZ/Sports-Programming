#include <bits/stdc++.h>
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1 << i) & x)

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int N = 1e4+10;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long f = 0;
    long long flow() {
        //long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
    vector<pair<int, int>> mincut()
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        vector<pair<int, int>> cut;
        bfs();
        for (auto & e: edges) {
            if (e.flow == e.cap && level[e.v] != -1 && level[e.u] == -1 && e.cap > 0) {
                cut.eb(e.v, e.u);
            }
        }
        return cut;
    }
};

void test() {
    /**
     * Podemos enxergar esse problema como um problema de achar um conjunto independente máximo, caso façamos o seguinte:
     * 
     * 1. Cada valor do vetor se comporta como um vértice em um grafo;
     * 2. Dois vértices tem ligação entre si se a soma entre eles resultar em um número primo.
     * 
     * Assim, queremos pegar o maior conjunto de vértices que não tem ligação entre si. Esse problema por si só é NP-Completo, mas podemos resolvê-lo
     * se o grafo em questão for bipartido. É possível enxergar que esse grafo montado é bipartido:
     * 
     * 1. Precisamos apenas de um número 1 do vetor, já que 1+1=2 e 2 é primo.
     * 2. Todos os outros primos são ímpares.
     * 3. Só é possível formar um número ímpar somando um número par e um número ímpar. Logo, a paridade dos valores é bipartida.
     * 
     * Assim, podemos rodar algum algoritmo de matching no grafo para achar o matching máximo dele. Assim, a gente acha a cobertura mínima de vértices, e 
     * como o problema de independência é complemento do problema de cobertura, podemos apenas fazer n - cobertura que achamos a quantidade de vértices no
     * conjunto independente. Aqui eu usei Dinic para implementar o matching, mas também tem o Hopcroft Karp para realizar o matching.
     */


    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    sort(all(a));
    vector<int> u;
    u.pb(a[0]);
    for(int i=1; i<n; i++) if(a[i] != 1) u.pb(a[i]);

    vector<int> p;
    bitset<N> b;

    b.set();
    b[0]=b[1]=false;
    for(int i=2; i*i<N; i++){
        if(b[i]){
            for(int j=i*i; j<N; j+=i) b[j]=false;
        }
    }

    for(int i=2; i<N; i++) if(b[i]) p.pb(i);
    
    auto is_prime = [&](int x) {
        for(auto pp: p){
            if(pp*pp > x) break;
            if(x%pp==0) return false;
        }
        return true;
    };

    n = u.size();

    int s = n+2, t = n+3;

    Dinic d(n+10, s, t);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j) continue;
            if(u[i]%2!=0 && u[j]%2==0){
                if(is_prime(u[i]+u[j])){
                    d.add_edge(i, j, d.flow_inf);
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        if(u[i]%2!=0){
            d.add_edge(s,i,1);
        }
        else{
            d.add_edge(i,t,1);
        }
    }
    cout << n-d.flow()<<"\n";
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
