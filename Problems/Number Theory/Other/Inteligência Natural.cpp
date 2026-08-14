// https://codeforces.com/group/SmO1tpanN1/contest/705528/problem/I

#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(x, i) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

// ordenar antes de usar essa funcao
#define make_unique(x) x.erase(unique(x.begin(), x.end()), x.end())https://codeforces.com/group/SmO1tpanN1/contest/705528/problem/I

using ll = long long;
using ld = long double;
using ull = unsigned int;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 50;

ll dp[N][N];

ll comb(int n, int k) {
    if(n<k) return 0;
    if(n == k) return 1;
    if(k == 0) return 1;
    if(~dp[n][k]) return dp[n][k];
    return dp[n][k] = comb(n-1,k) + comb(n-1,k-1);
}

int a[N];
int n, k;
ll l, r;

ll f(ll x) {
    ll rs = 0;
    for(int mask=0; mask<(1<<n);mask++){
        if(__builtin_popcount(mask)<k) continue;
        int k2 = __builtin_popcount(mask);
        ll lc=1;
        for(int i=0; i<n; i++){
            if(get_bit(mask,i)) lc=lcm(lc,a[i]);
        }
        if((k2-k)%2==0) rs+=comb(k2-1,k-1)*(x/lc);
        else rs-=comb(k2-1,k-1)*(x/lc);
    }
    return rs;
}

void test() {
    memset(dp,-1,sizeof dp);
    cin >> n >> k >> l >> r;
    // resolver f(0,x)

    for(int i=0; i<n; i++) cin >> a[i];
    cout<<f(r)-f(l-1)<<el;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
