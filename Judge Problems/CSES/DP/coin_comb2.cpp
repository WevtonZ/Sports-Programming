#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()

const int mod = 1e9+7;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    vector<vector<int>> dp(n+1, vector<int>(c+1, 0));
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(all(a));

    dp[0][0] = 1; // one way to form sum 0. Take nothing and there we go.

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= c; j++){
            if(i)
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
            if(j - a[i] >= 0){
                dp[i][j] = (dp[i][j] + dp[i][j-a[i]]) % mod;
            }
        }
    }

    cout << dp[n-1][c] << "\n";
    
    return 0;
}