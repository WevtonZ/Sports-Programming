// https://cses.fi/problemset/task/1144/

// reindex the array for the win!

#include<bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define pb push_back
 
typedef long double ld;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;
 
const int N = 1e6+5;
const ll inf = 1e9+100;
 
vector<int> a;
vector<int> reindex;
vector<pair<char,pair<int,int>>> queries;
int tree[N<<2];
 
int bb(int x){
    int l = 0, r = reindex.size()-1;
    while(l <= r){
        int m = (l+r)/2;
        if(reindex[m] <= x)
            l = m+1;
        else
            r = m-1;
    }
    return r+1;
}
 
int f(int a, int b){
    return a+b;
}
 
void updt(int p, int tl, int tr, int pos, bool ok){
    if(tl == tr){
        if(ok){
            tree[p]++;
        }
        else{
            tree[p]--;
        }
    }
    else{
        int tm = (tl+tr)>>1;
        if(pos <= tm)
            updt(lef(p), tl, tm, pos, ok);
        else
            updt(rig(p), tm+1, tr, pos, ok);
        
        tree[p] = f(tree[lef(p)], tree[rig(p)]);
    }
}
 
int find(int x, int tl, int tr, int l, int r){
    if(l > r)
        return 0;
    if(tl == l && tr == r){
        return tree[x];
    }
    else{
        int tm = (tr+tl)>>1;
        return f(find(lef(x), tl, tm, l, min(r, tm)), find(rig(x), tm+1, tr, max(l, tm+1), r));
    }
}
 
void test(){
    int n, q;
    cin >> n >> q;
    set<int> S;
 
    a.resize(n+1);
 
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        S.insert(a[i]);
    }
 
    for(int i = 0; i < q; i++){
        char c;
        int u, v;
        cin >> c >> u >> v;
        S.insert(u);
        S.insert(v);
        queries.pb({c,{u,v}});
    }
    int mx = 0;
 
    for(auto i: S){
        reindex.pb(i);
    }
 
    for(int i = 1; i <= n; i++){
        a[i] = bb(a[i]);
        mx = max(mx, a[i]);
    }
    
    for(int i = 0; i < q; i++){
        if(queries[i].ft == '?')
            queries[i].sd.ft = bb(queries[i].sd.ft);
        queries[i].sd.sd = bb(queries[i].sd.sd);
        mx = max(mx, queries[i].sd.sd);
    }
 
    for(int i = 1; i <= n; i++){
        updt(1, 1, mx, a[i], true);
    }
    for(int i = 0; i < q; i++){
        if(queries[i].ft == '!'){
            updt(1, 1, mx, a[queries[i].sd.ft], 0);
            a[queries[i].sd.ft] = queries[i].sd.sd;
            updt(1, 1, mx, a[queries[i].sd.ft], 1);
        }
        else{
            cout << find(1, 1, mx, queries[i].sd.ft, queries[i].sd.sd) << "\n";
        }
    }
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;  
    // cin >> teste;
 
    while(teste--){
        test();
    }
    
    return 0;
}
