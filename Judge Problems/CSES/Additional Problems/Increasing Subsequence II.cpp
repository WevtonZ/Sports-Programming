// https://cses.fi/problemset/task/1748

// counting things and then using a data structure to optimize it. Pretty much DP Optimization at this point

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define inbounds(x, l, r) ((l) <= (x) && (x) <= (r))
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
 
const int N = 2e5+10;
const int mod = 1e9+7;
 
int bit[N];
 
int f(int x, int y){
	return (x+y)%mod;
}
 
void updt(int x, int val){
	while(x < N){
		bit[x] = f(bit[x],val);
		x += x&-x;
	}
}
 
int get(int x){
	int rs=0;
	while(x){
		rs = f(rs,bit[x]);
		x -= x&-x;
	}
	return rs;
}
 
void loli(){
	int n;
	cin >> n;
 
	vector<int> a(n);
 
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
 
	set<int> S(all(a));
	vector<int> comp(all(S));
 
	auto bb = [&](int x){
		return lower_bound(all(comp), x) - comp.begin() + 1;
	};
 
	for(int i = 0; i < n; i++){ // coordinate compression
		a[i] = bb(a[i]);
	}
 
	int rs = 0;
	for(auto x: a){
		int s = 1 + get(x-1);
		rs = (rs+s)%mod;
		updt(x,s);
	}
 
	cout<<rs<<"\n";
}
 
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// cout<<fixed<<setprecision(12);
 
	int teste = 1;
	// cin >> teste;
	for(int l = 1; l <= teste; l++){
		loli();
	}
 
	return 0;
}
