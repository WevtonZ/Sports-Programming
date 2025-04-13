// https://codeforces.com/problemset/problem/1082/G

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdb;

#define ft first
#define sd second
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define pb push_back
#define eb emplace_back

struct FlowEdge {
    int v, u;
    ll cap, flow=0;
    FlowEdge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const ll flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m=0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, ll cap) {
        edges.eb(v,u,cap);
        edges.eb(u,v,0);
        adj[v].pb(m);
        adj[u].pb(m+1);
        m+=2;
    }

    bool bfs() {
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id: adj[v]) {
                if(edges[id].cap - edges[id].flow < 1) continue;
                if(level[edges[id].u] != -1) continue;
                level[edges[id].u]=level[v]+1;
                q.push(edges[id].u);
            }
        }
        return level[t]!=-1;
    }

    ll dfs(int v, ll pushed) {
        if(pushed == 0) return 0;
        if(v == t) return pushed;
        for(int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id=adj[v][cid];
            int u = edges[id].u;
            if(level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if(tr == 0) continue;
            edges[id].flow += tr;
            edges[id^1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll f=0;
    ll flow() {
        while(true) {
            fill(all(level), -1);
            level[s]=0;
            q.push(s);
            if(!bfs()) break;
            fill(all(ptr), 0);
            while(ll pushed = dfs(s, flow_inf)) f += pushed;
        }
        return f;
    }
};

void test() {
  /*
  Um problema de Matching usando Project Selection, onde as arestas são os nossos projetos e os vértices, nossas
  ferramentas. Com isso, podemos fazer o matching de aresta pra vértice e tacar um fluxo nisso.
  */
    int n, m;
    cin >> n >> m;

    ll rs = 0;
    vector<ll> a(n+1);
    int s = 0, t = m+n+99;
    Dinic dinic(m+n+100, s, t);
    for(int i=1; i<=n; i++){
        ll x;
        cin >> x;
        // adicionar arestas no sink.
        dinic.add_edge(m+i, t, x);
    }

    for(int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        rs += w; // somar todas as arestas da rede.
        dinic.add_edge(s, i, w);
        dinic.add_edge(i, u+m, dinic.flow_inf);
        dinic.add_edge(i, v+m, dinic.flow_inf);
    }

    cout << rs - dinic.flow() << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int t=1;
    // cin >> t;

    while(t--){
        test();
    }
    
    return 0;
}
