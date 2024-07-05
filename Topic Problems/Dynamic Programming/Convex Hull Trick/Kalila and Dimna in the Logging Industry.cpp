// https://codeforces.com/contest/319/problem/C

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const ll inf = 1e18;

struct line{
    mutable ll k, m, p;

    bool operator<(line const & o) const {
        return k > o.k;
    }

    bool operator<(ll x) const {
        return p<x;
    }
};

struct lineContainer : multiset<line,less<>>{
    static const ll inf = numeric_limits<ll>::max();
    
    ll div(ll a, ll b){
        return a/b - ((a^b)<0 && a%b);
    }

    bool isect(iterator x, iterator y){
        if(y == end()) return x->p = inf,0;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    void add(ll k, ll m){
        auto z = insert({k,m,0}), y = z++, x = y;
        while(isect(y,z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }

    ll query(ll x){
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k*x+l.m;
    }
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(0);

    int n;
    cin >> n;

    vector<ll> a(n+1,0), b(n+1,0);

    for(int i=1; i<=n; i++)
        cin >> a[i];
    
    for(int i=1; i<=n; i++)
        cin >> b[i];
    
    vector<ll> dp(n+1, inf);

    dp[1]=0;
    lineContainer S;
    S.add(b[1],0);

    for(int i = 2; i <= n; i++){
        dp[i]=S.query(a[i]);
        S.add(b[i], dp[i]);
    }

    cout<<dp[n]<<"\n";

    return 0;
}
