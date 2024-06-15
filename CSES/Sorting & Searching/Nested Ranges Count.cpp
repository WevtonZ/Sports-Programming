// https://cses.fi/problemset/task/2169

// using fenwick tree to update fast if a range is contained/contains another.

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
 
const int N = 4e5+5;
const int INF = 1e9+100;
 
vector<pair<pii,int>> a;
vector<int> contained, contain;
int bit[N];
vector<int> compress;
 
bool cmp(const pair<pii,int> & a, const pair<pii,int> &b){
    if(a.ft.ft > b.ft.ft){
        return 0;
    }
    else if(a.ft.ft == b.ft.ft){
        if(a.ft.sd < b.ft.sd){
            return 0;
        }
        else return 1;
    }
    else return 1;
}
 
int bb(int x){
    return (lower_bound(all(compress), x) - compress.begin() + 1);
}
 
void updt(int x, int val){
    while(x < N){
        bit[x] += val;
        x += (x&(-x));
    }
}
 
int find(int x){
    int ans = 0;
    while(x > 0){
        ans += bit[x];
        x -= (x&(-x));
    }
    return ans;
}
 
void test(){
    int n;
    cin >> n;
    
    a.resize(n);
    contained.assign(n, 0);
    contain.assign(n, 0);
    set<int> C;
 
    for(int i = 0; i < n; i++){
        cin >> a[i].ft.ft >> a[i].ft.sd;
        C.insert(a[i].ft.ft);
        C.insert(a[i].ft.sd);
        a[i].sd = i;
    }
 
    for(auto i: C){
        compress.pb(i);
    }
 
    C.clear();
 
    for(int i = 0; i < n; i++){
        a[i].ft.ft = bb(a[i].ft.ft);
        a[i].ft.sd = bb(a[i].ft.sd);
    }
 
    sort(all(a), cmp);
    
    int maxR, minR;
    maxR = 0, minR = INF;
 
    for(int i = 0; i < n; i++){
        contained[a[i].sd] += (find(N) - find(a[i].ft.sd-1));
        updt(a[i].ft.sd, 1);
    }
 
    memset(bit,0,sizeof(bit));
 
    for(int i = n-1; i >= 0; i--){
        contain[a[i].sd] += find(a[i].ft.sd);
        updt(a[i].ft.sd, 1);
    }
 
    for(auto i: contain){
        cout<<i<<" ";
    }
    cout<<"\n";
    for(auto i: contained){
        cout<<i<<" ";
    }
    cout<<"\n";
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
    // cin >> teste
 
    while(teste--){
        test();
    }
    
    return 0;
}
