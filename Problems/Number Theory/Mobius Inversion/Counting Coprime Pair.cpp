// https://cses.fi/problemset/task/2417/

#include <bits/stdc++.h>
using namespace std;
 
#pragma region
 
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
 
using ll = long long;
using ld = long double;
 
template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#pragma endregion
 
const int N = 1e6+10;
 
ll mu[N];
 
void sieve() {
    mu[1] = 1;
    for(int i=2; i<N; i++){
        mu[i]--;
        for(int j=i+i; j<N; j+=i) mu[j] -= mu[i];
    }
}
 
void test() {
    sieve();
    int n;
    cin >> n;
 
    vector<ll> a(N, 0);
    for(int i=0; i<n; i++){
        int x; cin >> x;
        a[x]++;
    }
 
    for(int i=1; i<N; i++){
        for(int j=i+i; j<N; j+=i){
            a[i] += a[j];
        }
    }
 
    ll rs = 0;
 
    for(int i=1; i<N; i++) {
        rs += mu[i] * 1ll * (a[i]*(a[i]-1))/2;
    }
    cout << rs << "\n";
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);
 
    int tt=1;
    // cin >> tt;
 
    while(tt--){
        test();
    }
    
    return 0;
}
