// https://cses.fi/problemset/task/1644/

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
 
const int N = 2e5+5;
const int mod = 1e9+7;
const ll inf = 1e18;
 
multiset<ll> S;
vector<int> x;
vector<ll> pf;
 
void test(){
    int n, a, b;
    cin >> n >> a >> b;
 
    x.resize(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }
    pf.pb(0);
    for(int i = 0; i < n; i++){
        pf.pb(pf.back() + x[i]);
    }
 
    ll ans = -inf;
    for(int i = a; i <= n; i++){
        S.insert(pf[i-a]);
        ans = max(ans, pf[i] - *S.begin());
        if(i >= b) S.erase(S.find(pf[i-b]));
    }
 
    cout << ans << "\n";
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
