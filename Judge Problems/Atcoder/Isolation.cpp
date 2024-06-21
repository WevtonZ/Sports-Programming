// https://atcoder.jp/contests/abc302/tasks/abc302_e

// problem on graphs with a very pretty solution

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

const int N = 3e5+5;

set<int> e[N];

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    int rs=n;

    while(q--){
        int t; cin >> t;
        if(t==1){
            int u, v;
            cin >> u >> v;
            if(e[u].empty()) rs--;
            if(e[v].empty()) rs--;
            e[u].emplace(v);
            e[v].emplace(u);
        }
        else{
            int u;
            cin >> u;
            for(auto i: e[u]){
                if(e[i].size()==1) rs++;
                e[i].erase(u);
            }
            if(!e[u].empty())
                rs++;
            e[u].clear();
        }

        cout<<rs<<"\n";
    }

    return 0;
}
