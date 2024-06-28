// https://codeforces.com/gym/103960/problem/H

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

const int N = 1e4+5;

vector<int> e[N], re[N];
vector<int> ord, comp;

vector<vector<int>> adj_scc;

vector<bool> vis;
void dfs1(int x){
    vis[x]=true;

    for(auto i: e[x]){
        if(!vis[i]){
            dfs1(i);
        }
    }
    ord.pb(x);
}

void dfs2(int x){
    vis[x]=true;
    comp.pb(x);
    for(auto i: re[x]){
        if(!vis[i]){
            dfs2(i);
        }
    }
}

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(0);

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        int x, y;
        cin >> x >> y;
        e[x].pb(y);
        re[y].pb(x);
    }

    vis.assign(n+1, false);

    for(int i = 1; i <= n; i++){
        if(!vis[i]) dfs1(i);
    }


    vis.assign(n+1,false);
    reverse(all(ord));
    adj_scc.resize(n+1);
    vector<int> r(n+1,0);
    vector<int> roots;
    int cor=1;
    
    for(auto i: ord){
        if(!vis[i]){
            dfs2(i);

            for(auto j: comp){
                r[j]=cor;
            }
            roots.pb(cor);
            comp.clear();
            cor++;
        }
    }

    vector<int> indegree(cor,0), outdegree(cor,0);

    for(int i = 1; i <= n; i++){
        for(auto j: e[i]){
            int ru = r[i];
            int rv = r[j];

            if(ru!=rv){
                adj_scc[ru].pb(rv);
                indegree[rv]++;
                outdegree[ru]++;
            }
        }
        // cout<<"aqui estou oiiiiiiiiiiiii\n";
    }

    int rs_roots, rs_leaves;
    rs_roots = rs_leaves = 0;

    for(int i = 1; i < cor; i++){
        if(indegree[i]==0) rs_roots++;
        if(outdegree[i]==0) rs_leaves++;
    }
    if(cor==2){
        cout<<"0\n";
    }
    else{
        cout<<max(rs_roots,rs_leaves)<<"\n";    
    }

    return 0;
}
