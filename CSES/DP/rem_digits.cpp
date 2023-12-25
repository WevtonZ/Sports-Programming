#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+10;

int dp[N];

int solve(int n){// what number I am now.
    if(n < 0) return N;
    if(n == 0) return 0;

    int &ans = dp[n];
    if(ans != -1) return ans;
    ans = N;

    string s = to_string(n);
    for(auto i: s){
        if(i == '0') continue;
        ans = min(ans, 1 + solve(n - (i-'0')));
    }
    
    return ans;
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    fill(dp, dp+n+1, -1);
    cout << solve(n) << "\n";

    return 0;
}