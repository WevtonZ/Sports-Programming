// https://cses.fi/problemset/task/1680

// very nice problem on pushing the answer foward. Had a bunch of mistakes in this one.

#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;
typedef pair<ll,ll> pll;
 
#define pb push_back
#define ft first
#define sd second
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
 
const int N = 2e5+5;
const int inf = 1e9;
 
int dist[N], indegree[N], parent[N];
vector<int> edges[N], back_edges[N];
vector<bool> vis;
 
void test(){
    int n, m;
    cin >> n >> m;
    vis.assign(n+1, false);
 
    for(int i = 1; i <= n; i++){
        dist[i] = -inf;
    }
 
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        indegree[v]++;
        edges[u].pb(v);
        back_edges[v].pb(u);
    }
 
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(indegree[i] == 0)
            q.push(i);
    }
 
    memset(parent, -1, sizeof(parent));
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
 
        for(auto v: edges[u]){
            indegree[v]--;
            if(indegree[v] == 0){
                q.push(v);
            }
        }
 
        int mx = -inf, par = -1;
 
        for(auto i: back_edges[u]){
            if(dist[i] + 1 > mx){
                mx = dist[i]+1;
                par = i;
            }
        }
 
        dist[u] = mx;
        if(u == 1) dist[u] = 1;
        parent[u] = par;
    }
 
    vector<int> ans;
    bool ok = false;
    int tmp = n;
 
    if(tmp == 1) ok = true;
    
    while(tmp != -1 && !ok){
        ans.pb(tmp);
        if(tmp == 1) ok = true;
        tmp = parent[tmp];
    }
 
    if(!ok){
        cout << "IMPOSSIBLE\n";
    }
    else{
        cout<<ans.size()<<"\n";
        reverse(all(ans));
        for(auto i: ans)
            cout << i << " ";
        cout << "\n";
    }
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
 
    while(teste--){
        test();
    }
 
    return 0;
}
