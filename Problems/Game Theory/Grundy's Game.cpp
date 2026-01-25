// https://cses.fi/problemset/task/2207/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define dbg(x) cout << #x << " = " << x << "\n"
 
const int inf = 1e9;
const int N = 2e5+3;
 
int dp[N];
 
int mex(set<int> &S){ // O(x log x)
    int x = 0;
    while(S.find(x) != S.end()) x++;
    return x;
}
 
int grundy(int n){
    if(n <= 2) return 0;
    if(dp[n] != -1) return dp[n];
    set<int> S;
    for(int i = 1; i+i < n; i++){
        S.insert(grundy(i) ^ grundy(n-i));
    }
    return dp[n] = mex(S);
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    memset(dp,-1,sizeof(dp));
 
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        if(n > 1500) cout<<"first\n";
        else{
            cout<<(grundy(n) != 0 ? "first" : "second") << "\n";
        }
    }
 
    return 0;
}
