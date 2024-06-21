// https://cses.fi/problemset/task/1661

// problema da soma for the win

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5+100;
 
map<ll,int> M;
vector<ll> a;
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    ll n, k;
    cin >> n >> k;
 
    a.resize(n);
    for(auto &i: a){
        cin >> i;
    }
    
    M[0] = 1;
    ll sum = 0;
    ll ans = 0;
 
    for(int i = 0; i < n; i++){
        sum += a[i];
        ans += M[sum-k];
        M[sum]++;
    }
 
    cout << ans << '\n';
 
    return 0;
}
