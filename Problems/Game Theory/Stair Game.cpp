// https://cses.fi/problemset/task/1099/

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
 
void loli(){
	int n;
	cin >> n;
	vector<int> a(n);
 
	int qt=0;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		if((i&1)) qt^=a[i];
	}
	if(qt) cout<<"first\n";
	else cout<<"second\n";
}
 
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// cout<<fixed<<setprecision(12);
 
	int teste = 1;
	cin >> teste;
	for(int l = 1; l <= teste; l++){
		loli();
	}
 
	return 0;
}
 
