// https://cses.fi/problemset/task/2194/

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
 
using ll = long long;
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
 
    vector<pair<ll,ll>> a(n);
    for(int i=0; i<n; i++) cin >> a[i].ft >> a[i].sd;
 
    sort(all(a));
 
    auto dist = [&](pair<ll,ll> x, pair<ll,ll> y) -> ll {
        return (x.ft-y.ft)*(x.ft-y.ft)+(x.sd-y.sd)*(x.sd-y.sd);
    };
 
    ll d = 8e18;
    set<pair<ll,ll>> S;
    
    int j = 0;
    for(int i=0; i<n; i++) {
        ll val = ceil(sqrtl(d));
        while(a[i].ft - a[j].ft >= val){
            S.erase(make_pair(a[j].sd, a[j].ft));
            j++;
        }
 
        auto x = S.lower_bound({a[i].sd-val, a[i].ft});
        auto y = S.upper_bound({a[i].sd+val, a[i].ft});
 
        for(auto k = x; k != y; k++){
            d = min(d, dist(make_pair(k->sd, k->ft), a[i]));
        }
 
        S.insert(make_pair(a[i].sd, a[i].ft));
    }
 
    cout << d << "\n";
 
    return 0;
}
