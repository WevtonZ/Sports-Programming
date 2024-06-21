// https://codeforces.com/problemset/problem/1707/B

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

const int N = 5e5+10;
const ll inf = 1e9+10;

void loli(){
	int n;
	cin >> n;

	map<int,int> M;

	for(int i = 0; i < n; i++){
		int x; cin >> x;
		M[x]++;
	}

	while(M.size() > 1 || M.begin()->sd > 1){
		map<int,int> M2;

		for(auto [x, y]: M){
			if(y>1) M2[0] += y-1;
		}

		auto it = ++M.begin();
		int ls = M.begin()->ft;
		while(it != M.end()){
			M2[it->ft - ls]++;
			ls = it->ft;
			it++;
		}
		swap(M,M2);	
	}

	cout<<M.begin()->ft<<"\n";
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// cout<<fixed<<setprecision(12);

	int __ = 1;
	cin >> __;
	for(int _ = 1; _ <= __; _++){
		loli();
	}

	return 0;
}
