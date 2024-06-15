/*
    https://cses.fi/problemset/task/1734
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back
 
const int N = 200005;
 
int bit[N];
 
void updt(int x, int val){
    x++;
    while(x < N){
        bit[x] += val;
        x += x&-x;
    }
}
 
int get(int x){
    x++;
    int rs=0;
    while(x){
        rs += bit[x];
        x -= x&-x;
    }
    return rs;
}
 
void loli(){
    int n, q;
    cin >> n >> q;
 
    vector<int> a(n);
    for(auto &i: a)
        cin >> i;
    
    vector<vector<pair<int,int>>> queries(n);
 
    for(int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        x--, y--;
        queries[x].pb(mp(y,i));
    }
 
    map<int,int> lst;
    vector<int> rs(q);
 
    for(int i = n-1; i >= 0; i--){
        int x = a[i];
 
        if(lst.count(x)>0) updt(lst[x],-1);
        lst[x]=i;
        updt(i,1);
 
        for(auto &[u,v]: queries[i]){
            rs[v]=get(u);
        }
    }
 
    for(auto i: rs)
        cout<<i<<" ";
    cout<<"\n";
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int teste = 1;
    // cin >> teste;
 
    for(int i = 1; i <= teste; i++){
        loli();
    }
 
    return 0;
}
