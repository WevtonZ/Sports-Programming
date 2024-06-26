// https://cses.fi/problemset/task/1711/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
 
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
 
    long long flow() {
        long long f = 0;
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
 
vector<int> path;
int source, sink;
 
void find_path(int x, Dinic & d){
	path.pb(x);
	for(auto i: d.adj[x]){
		if(d.edges[i].flow > 0){
			d.edges[i].flow--;
			find_path(d.edges[i].u, d);
			break;
		}
	}
 
	if(x == sink){
		cout<<path.size()<<"\n";
		for(auto i: path) cout<<i<<" ";
		cout<<"\n";
	}
}
 
void test(){
	int n, m;
	cin >> n >> m;
 
	source = 1, sink = n;
 
	Dinic d(n+1, source, sink);
 
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		d.add_edge(u, v, 1);
	}
	ll ans = d.flow();
	cout << ans << "\n";
	while(ans--){
		find_path(source, d);
		path.clear();
	}
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(6);
 
    int teste = 1;
    // cin >> teste;
 
    while(teste--){
        test();
    }
}
