// https://cses.fi/problemset/task/1130/

// There is a greedy strategy on this problem that is: match the leaves as much as you possibly can,
// and that will give you the maximum matching on a tree. In general graphs it does not work, but works
// fine on a tree.

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define pb push_back

typedef long long ll;

const int N = 2e5+3;
 
vector<int> e[N];
int ans;
int mark[N];
 
void dfs(int x, int p = -1){
    for(auto i: e[x]){
        if(i != p){
            dfs(i, x);
            if(!mark[i] && !mark[x]){
                mark[i] = ++mark[x];
                ans++;
            }
        }
    }
}
 
void test(){
    int n;
    cin >> n;
    
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
 
    dfs(1);
    cout<<ans<<"\n";
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
    // cin >> teste;
 
    while(teste--){
        test();
    }
 
    return 0;
}
