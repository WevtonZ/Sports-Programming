// https://codeforces.com/gym/101982

#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
// #pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
using ll = long long;
#define dbg(x) cout << #x << " = " << x << '\n';
// #define int long long // tiagopio

const int N = 1e7+2;

int mu[N];
bool is_composite[N];
vector<int> prime;

void mobius(int n) {
    fill(is_composite, is_composite+n, false);
    mu[1]=1;
    for(int i=2; i<n; i++){
        if(!is_composite[i]){
            prime.pb(i);
            mu[i] = -1;
        }
        for(int j=0; j<prime.size() && i*prime[j] < n; j++) {
            is_composite[i*prime[j]] = true;
            if(i%prime[j] != 0){ // sao coprimos
                mu[i*prime[j]] = mu[i] * mu[prime[j]];
            }
            else{ // nao sao coprimos
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
}

ll F(int n, int m) {
    ll rs=0;
    for(int d=1; d<=min(n,m); d++){
        rs += mu[d] * 1ll * (n/d) * (m/d);
    }
    return rs;
}

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    mobius(max(b,d)+1);
    cout<<F(b,d)-F(a-1,d)-F(b,c-1)+F(a-1,c-1)<<"\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
