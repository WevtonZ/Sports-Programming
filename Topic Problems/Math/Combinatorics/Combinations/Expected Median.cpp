// https://codeforces.com/contest/1999/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x)+1)

#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5+10;
const ll mod=1e9+7;

ll fat[N], ifat[N];

ll fexp(ll a,ll b){
	ll rs=1;
	while(b){
		if(1&b) rs=rs*a%mod;
		a=a*a%mod;
		b>>=1ll;
	}
	return rs;
}

void init(){
	fat[0]=ifat[0]=1;
	for(ll i=1; i<N; i++){
		fat[i]=fat[i-1]*i%mod;
		ifat[i]=fexp(fat[i],mod-2);
	}
}

ll comb(ll a, ll b) {
	if(b<0) return 0;
	if(b>a) return 0;
	return fat[a]*ifat[b]%mod*ifat[a-b]%mod;
}

void test() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	int x=0;
	for(int i=0; i<n; i++){
		cin>>a[i];
		x+=a[i];
	}

	ll rs=0;
	for(int i=k/2+1; i<=x; i++) {
		rs=(rs+comb(x,i)*comb(n-x,k-i)%mod)%mod;
	}

	cout<<rs<<"\n";
}

int32_t main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	// cout<<fixed<<setprecision(12);
	init();

	int __ = 1;
	cin >> __;
	for(int _ = 1; _ <= __; _++){
		test();
	}

	return 0;
}
