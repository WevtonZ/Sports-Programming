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
 
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

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
    /*
        Como fazer um Project Selection:

        1. Nesse problema, temos N tipos de vodka e M categorias de vodka. Cada tipo de vodka tem um preço, e se combinadas
        elas podem gerar um benefício B para quem bebe.

        2. Podemos modelar esse problema como um Project Selection, onde fazemos um Source ligar para todos os benefícios,
        fazemos todos os custos serem ligados no sink e fazemos as ligações dos benefícios nas categorias, com capacidade
        infinita nessas arestas no meio do matching.

        3. Por fim, rodamos o fluxo nelas, onde a resposta para maximizar o benefício é somaBeneficios-maxFlow.
    */
    int n, m;
    while(cin >> n >> m) {
        int source, sink, total;
        total = n+m+100;
        source = n+m+51, sink = n+m+50;
        Dinic d(total, source, sink);

        int rs=0;
        int C; // custo da vodka.
        for(int i=1; i<=n; i++){
            // ligar esses caras no sink.
            cin >> C;
            d.add_edge(i+m, sink, C);
        }
        
        vector<int> p(m+1); // quantas categorias de vodka o i-esimo cara tem.
        for(int i=1; i<=m; i++) cin >> p[i];

        int B; // lucro da vodka

        for(int i=1; i<=m; i++) {
            // ligar esses caras no source.
            cin >> B;
            rs+=B;
            d.add_edge(source, i, B);

            for(int j=1; j <= p[i]; j++) {
                // ligar esses caras entre eles.
                int x;
                cin >> x;
                d.add_edge(i, x+m, d.flow_inf);
            }
        }

        cout << rs-d.flow() << "\n";
    }
}

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(11);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
