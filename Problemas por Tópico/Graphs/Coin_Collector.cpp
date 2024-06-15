#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)

#define ft first
#define sd second
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple 
 
const int N = 2e5+10;
 
vector<int> e[N], re[N];
vector<bool> vis;
vector<int> ord, comp;
vector<int> r;
vector<int> r_n;
vector<vector<int>> scc;
vector<ll> a;
ll dp[N];
 
void dfs1(int x){
    vis[x]=true;
    for(auto u: e[x]){
        if(!vis[u]){
            dfs1(u);
        }
    }
    ord.pb(x);
}
 
ll dfs2(int x){
    vis[x]=true;
    ll tmp = 0;
    comp.pb(x);
    for(auto i: re[x]){
        if(!vis[i]){
            tmp += dfs2(i);
        }
    }
    tmp += a[x];
    return tmp;
}
 
ll dfs3(int x){
    vis[x] = true;
    dp[x] = a[x];
 
    for(auto i: scc[x]){
        if(!vis[i]){
            dp[x] = max(dp[x], dfs3(i)+a[x]);
        }
        else{
            dp[x] = max(dp[x], a[x]+dp[i]);
        }
    }
    return dp[x];
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    ll coin = 0;
    cin >> n >> m;
 
    a.resize(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
 
    for(int i = 1; i <= m; i++){
        int a, b;
        cin >> a >> b;
        e[a].pb(b);
        re[b].pb(a);
    }
 
    vis.assign(n+10,false);
    for(int i = 1; i <= n; i++){
        if(!vis[i])
            dfs1(i);
    }
 
    vis.assign(n+10,false);
    reverse(all(ord));
 
    r.assign(n+1,0);
    scc.resize(n+1);
    
    for(auto v: ord){
        if(!vis[v]){
            coin = dfs2(v);
            int root = comp.front();
            for(auto u: comp){
                r[u] = root;
            }
            r_n.pb(root);
            a[root] = coin;
 
            comp.clear();
        }
    }
 
    for(int i = 1; i <= n; i++){
        for(auto u: e[i]){
            int r_v = r[i];
            int r_u = r[u];
 
            if(r_u != r_v){
                scc[r_v].pb(r_u);
            }
        }
    }
 
    ll ans = 0;
 
    vis.assign(n+1,false);
 
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            dfs3(i);
        }
    }
 
    for(int i = 1; i <= n; i++){
        ans = max(ans, dp[i]);
        // cout<<dp[i]<<"\n";
    }
 
    cout << ans << '\n';
 
    return 0;
}