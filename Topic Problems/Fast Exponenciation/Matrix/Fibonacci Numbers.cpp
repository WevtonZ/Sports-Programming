// https://cses.fi/problemset/task/1722

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll mod = (ll)1e9+7;
 
void product(ll f[2][2], ll b[2][2])
{
    ll w = ((f[0][0] * b[0][0]) + (f[0][1] * b[1][0]));
    ll x = ((f[0][0] * b[0][1]) + (f[0][1] * b[1][1]));
    ll y = ((f[1][0] * b[0][0]) + (f[1][1] * b[1][0]));
    ll z = ((f[1][0] * b[0][1]) + (f[1][1] * b[1][1]));
 
    f[0][0] = w%mod;
    f[0][1] = x%mod;
    f[1][0] = y%mod;
    f[1][1] = z%mod;
}
 
ll power(ll f[2][2], ll n){
    ll b[2][2] = {{1, 0}, {0, 1}};
 
    while(n){
        if(1&n) product(b, f);
        product(f, f);
        n>>=1LL;
    }
    return b[0][0];
}
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    ll n;
    cin >> n;
 
    ll fib[2][2];
    fib[0][0] = fib[0][1] = fib[1][0] = 1LL;
    fib[1][1] = 0LL;
 
    if(n == 0){
        cout << 0 << '\n';
        return 0;
    }
 
    cout << power(fib,n-1) << '\n';
 
    return 0;
}
