#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
 
struct Edge{
    int u, v, weight;
    bool operator<(Edge const& a){
        return weight < a.weight;
    }
};
 
vector<int> parent, rq;
vector<Edge> e, res;
 
void make_set(int x){
    parent[x] = x;
    rq[x] = 0;
}
 
int find(int x){
    if(x == parent[x]) return x;
    return parent[x] = find(parent[x]);
}
 
void union_(int u, int v){
    u = find(u);
    v = find(v);
 
    if(u != v){
        if(rq[u] < rq[v]){
            swap(u, v);
        }
        parent[v] = u;
        if(rq[u] == rq[v]){
            rq[u]++;
        }
    }
}
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    parent.assign(n+10, 0);
    rq.assign(n+10, 0);
 
    for(int i = 1; i <= n; i++){
        make_set(i);
    }
 
    for(int i = 1, a, b, c; i <= m; i++){
        cin >> a >> b >> c;
        e.push_back({a, b, c});
    }
 
    sort(e.begin(), e.end());
 
    ll cost = 0;
 
    for(auto i: e){
        if(find(i.u) != find(i.v)){
            cost += i.weight;
            res.push_back(i);
            union_(i.u, i.v);
        }
        if(res.size() == n-1) break;
    }
 
    if(res.size() == n-1) cout << cost << '\n';
    else cout << "IMPOSSIBLE\n";
 
    return 0;
}