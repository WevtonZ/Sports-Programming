// https://cses.fi/problemset/task/1691

#include <bits/stdc++.h>
using namespace std;
 
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
 
#define rep(i, begin, end) for(__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2*((begin) > (end)))
 
// using i128 = __int128_t;
using ll = long long;
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
 
const int N = 1e5+10;
 
set<int> graph[N];
vector<int> deg;
vector<int> rs;
 
void dfs(int x) {
    while(graph[x].size()){
        int y = *graph[x].begin();
        graph[x].erase(y);
        graph[y].erase(x);
        dfs(y);
    }
    rs.pb(x);
}
 
void test() {
    int n, m;
    cin>>n>>m;
 
    deg.assign(n+1, 0);
 
    for(int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        graph[x].insert(y);
        graph[y].insert(x);
        deg[x]++, deg[y]++;
    }
 
    for(int i=1; i<=n; i++){
        if((1&deg[i])){
            cout<<"IMPOSSIBLE\n";
            return;
        }
    }
 
    dfs(1);

    for(int i=1; i<=n; i++){
        if(graph[i].size() > 0){
            cout<<"IMPOSSIBLE\n";
            return;
        }
    }

    for(int i=0; i<rs.size(); i++){
        cout<<rs[i]<<" ";
    }
    cout<<"\n";
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
