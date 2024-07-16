#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const int N = 2e5+10;

vector<int> e[N];
vector<int> leaves; // leaves to enumerate.

void dfs(int x, int p){
    for(auto i: e[x]){
        if(i != p){
            dfs(i, x);
        }
    }

    if(e[x].size() == 1){
        leaves.pb(x);
    }
}

void loli(){
    int n, h;
    cin >> n >> h;

    for(int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        e[x].pb(y);
        e[y].pb(x);
    }
    dfs(h,h);
    int tmp = (leaves.size()+1)/2;
    cout<<tmp<<"\n";
    for(int i = 0; i+tmp < leaves.size(); i++){ 
        cout<<leaves[i]<<" "<<leaves[i+tmp]<<"\n";
    }
    if(leaves.size()&1){
        cout<<leaves[leaves.size()/2]<<" "<<h<<"\n";
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(12);

    int __ = 1;
    // cin >> __;

    for(int _ = 1; _ <= __; _++){
        loli();
    }
    
    return 0;
}
