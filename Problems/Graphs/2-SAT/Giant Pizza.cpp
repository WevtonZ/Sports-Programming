// https://cses.fi/problemset/task/1684

#include <bits/stdc++.h>
using namespace std;
 
struct SAT{
	int nodes;
	vector<vector<int>> adj, r_adj;
	vector<bool> vis;
	vector<int> comp, order;
	vector<bool> ans;
 
	SAT(int n){
		this->nodes = 2*n+1;
		adj.resize(nodes);
		r_adj.resize(nodes);
		comp.assign(nodes, 0);
		ans.assign(n,false);
	}
 
	void dfs1(int u){
		vis[u]=true;
		for(auto v: adj[u]){
			if(!vis[v]) dfs1(v);
		}
		order.push_back(u);
	}
 
	void dfs2(int u, int c){
		comp[u] = c;
		for(auto v: r_adj[u]){
			if(comp[v] == 0)
				dfs2(v,c);
		}
	}
 
	void add_edge(int u, int v, bool flag){
		if(flag == 0){ // adicionar na lista normal
			adj[u].push_back(v);
		}
		else{ // adicionar na lista reversa
			r_adj[u].push_back(v);
		}
	}
 
	// a -> ~a
	int neg(int u){
		return (u^1);
	}
 
	// (a v b) == (~a -> b) & (~b -> a)
	void add_or(int u, bool bu, int v, bool bv){
		u = (2*u)|bu;
		v = (2*v)|bv;
 
		add_edge(neg(u),v,0);
		add_edge(v,neg(u),1);
		add_edge(neg(v),u,0);
		add_edge(u,neg(v),1);
	}
 
	// (a ^ b) == (a -> b) & (~b -> ~a)
	void add_xor(int u, bool bu, int v, bool bv){
		u = (2*u)|bu;
		v = (2*v)|bv;
 
		add_edge(u,v,0);
		add_edge(v,u,1);
		add_edge(neg(v),neg(u),0);
		add_edge(neg(u),neg(v),1);
	}
 
	bool solve(){
		vis.assign(nodes,false);
		for(int i = 0; i < nodes; i++){
			if(!vis[i]) dfs1(i);
		}
 
		int color = 1;
 
		reverse(order.begin(), order.end());
		for(auto i: order){
			if(comp[i] == 0){
				dfs2(i, color);
				color++;
			}
		}
 
		for(int i = 0; i < nodes/2; i++){
			int v = (i<<1);
			if(comp[v] == comp[v+1]){
				return false;
			}
			ans[i] = comp[v] > comp[v+1];
		}
 
		return true;
	}
};
 
int32_t main(){
	cin.tie(nullptr)->sync_with_stdio(false);
 
	int n, m;
	cin >> n >> m;
 
	SAT sat(m+1);
 
	for(int i = 0; i < n; i++){
		int x, y;
		char c, d;
		cin >> c >> x >> d >> y;
		bool nc = c == '+';
		bool nd = d == '+';
 
		sat.add_or(x,nc,y,nd);
	}
 
	if(sat.solve() == false){
		cout<<"IMPOSSIBLE\n";
	}
	else{
		for(int i = 1; i <= m; i++){
			cout<<(sat.ans[i]==0?"+":"-")<<" ";
		}
		cout<<"\n";
	}
 
	return 0;
}
