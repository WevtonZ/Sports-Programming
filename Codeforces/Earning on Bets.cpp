// https://codeforces.com/contest/1979/problem/C

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)

#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const int N = 1e5+10;
const ll inf = 1e9+10;

void celebi(){
	int n;
	cin >> n;
	vector<ll> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	ll x=1;
	for(int i = 0; i < n; i++){
		x = lcm(x,a[i]);
	}
	ll sum=0;
	for(int i = 0; i < n; i++){
		sum+=x/a[i];
	}
	if(sum>=x){
		cout<<"-1\n";
	}
	else{
		for(auto i: a)
			cout<<x/i<<" ";
		cout<<"\n";
	}
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// cout<<fixed<<setprecision(12);

	int teste = 1;
	cin >> teste;
	for(int l = 1; l <= teste; l++){
		celebi();
	}

	return 0;
}
