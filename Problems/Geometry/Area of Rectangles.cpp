// https://cses.fi/problemset/task/1741/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define eb emplace_back
 
const int inf = 1e9+7;
const int N = 2e6+10;
const int emp = 0;
const int offset = 1e6+1;
 
pair<int,int> tree[N << 2];
int lazy[N << 2];
 
struct events{
    int x, y1, y2, type;
 
    events(int x, int y1, int y2, int type) : x(x), y1(y1), y2(y2), type(type) {}
};
 
bool cmp(events a, events b){
    return a.x < b.x;
}
 
pair<int,int> f(pair<int,int> a, pair<int,int> b){
    if(a.ft < b.ft)
        return a;
    if(a.ft > b.ft)
        return b;
    return mp(a.ft, a.sd + b.sd);
}
 
void push(int x, int tl, int tr){
    if(lazy[x] == emp || tl == tr) return;
 
    int tm = tl + tr >> 1;
 
    lazy[lef(x)] += lazy[x];
    lazy[rig(x)] += lazy[x];
 
    tree[lef(x)].ft += lazy[x];
    tree[rig(x)].ft += lazy[x];
 
    lazy[x] = emp;
}
 
void build(int x, int tl, int tr){
    if(tl == tr){
        tree[x] = {0, 1};
    }
    else{
        int tm = tl + tr >> 1;
        build(lef(x), tl, tm);
        build(rig(x), tm+1, tr);
        tree[x] = f(tree[lef(x)], tree[rig(x)]);
    }
}
 
pair<int,int> get(int x, int tl, int tr, int l, int r){
    if(tl > r || tr < l)
        return mp(inf, 0);
    if(tl >= l && tr <= r)
        return tree[x];
 
    push(x, tl, tr);
    int tm = tl + tr >> 1;
    pair<int,int> f1 = get(lef(x), tl, tm, l, r);
    pair<int,int> f2 = get(rig(x), tm+1, tr, l ,r);
    return f(f1, f2);
}
 
void updt(int x, int tl, int tr, int l, int r, int val){
    if(tl > r || tr < l)
        return;
    if(tl >= l && tr <= r){
        tree[x].ft += val;
        lazy[x] += val;
        return;
    }
    push(x, tl, tr);
    int tm = tl + tr >> 1;
    updt(lef(x), tl, tm, l, r, val);
    updt(rig(x), tm+1, tr, l, r, val);
    tree[x] = f(tree[lef(x)], tree[rig(x)]);
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Podemos fazer um line sweep e manter quais caras eu tenho ativo agora. Podemos usar uma segment tree para guardar isso.
  
    int n;
    cin >> n;
    
    build(1, 1, N);
 
    vector<vector<events>> a(N+1);
 
    for(int i = 0; i < n; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[x1+offset].eb(x1, y1+offset, y2+offset-1, 0);
        a[x2+offset].eb(x2, y1+offset, y2+offset-1, 1);
    }
    
    ll rs = 0;
 
    for(int i = 0; i <= N; i++){
        for(events j: a[i]){
            if(j.type == 0){
                updt(1, 1, N, j.y1, j.y2, 1);
            }
            else{
                updt(1, 1, N, j.y1, j.y2, -1);
            }
 
        }
 
        pair<int,int> r = get(1, 1, N, 1, N);
        if(r.ft == 0){
            rs += N - r.sd;
        }
        else{
            rs += N;
        }
    }
 
    cout << rs << '\n';
 
    return 0;
}
