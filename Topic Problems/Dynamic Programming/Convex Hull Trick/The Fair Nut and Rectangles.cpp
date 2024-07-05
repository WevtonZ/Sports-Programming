// https://codeforces.com/contest/1083/problem/E

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct lineContainer : multiset<Line, less<>> {
	static const ll inf = numeric_limits<ll>::max();

	ll div(ll a, ll b){
		return a / b - ((a ^ b) < 0 && a % b);
    }
	
    bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	
    void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	
    ll query(ll x) {
		assert(!empty());
		auto l = lower_bound(x);
		return l->k * x + l->m;
	}
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<tuple<ll,ll,ll>> a(n);
    for(auto &[p, q, c]: a)
        cin >> p >> q >> c;
    
    sort(all(a));

    lineContainer S;
    S.add(0, 0);

    ll rs = 0;

    for(int i = 0; i < n; i++){
        auto [p, q, cost] = a[i];
        ll x = S.query(q)+p*q-cost;
        rs = max(rs,x);
        S.add(-p, x);
    }

    cout<<rs<<"\n";

    return 0;
}
