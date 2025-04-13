// https://codeforces.com/contest/776/problem/D

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

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

    void add_imp(int u, int v){
        adj[u].push_back(v);
        r_adj[v].push_back(u);
    }

    // (a para ~a ou ~a para a)
    int neg(int u){
        return (u^1);
    }

    // (a v b) == (~a -> b) & (~b -> a)
    void add_or(int u, bool bu, int v, bool bv){
        u = (2*u)|bu;
        v = (2*v)|bv;

        add_imp(neg(u),v);
        add_imp(neg(v),u);
    }


    void add_xor(int u, int v, bool ng){
        if(ng == 0){
            add_or(u,0,v,0);
            add_or(v,1,u,1);
        }
        else{
            add_or(u,1,v,0);
            add_or(u,0,v,1);
        }
    }

    // simbora!
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

    vector<vector<int>> gp(n+1);

    vector<int> cor(n+1);
    for(int i = 1; i <= n; i++)
        cin >> cor[i];

    for(int i = 0; i < m; i++){
        int x; cin >> x;
        for(int j = 0; j < x; j++){
            int k; cin >> k;
            gp[k].push_back(i);
        }
    }

    for(int i = 1; i <= n; i++){
        int u = gp[i][0];
        int v = gp[i][1];
        sat.add_xor(u,v,cor[i]);
    }

    if(sat.solve())
        cout<<"YES\n";
    else
        cout<<"NO\n";

    return 0;
}
