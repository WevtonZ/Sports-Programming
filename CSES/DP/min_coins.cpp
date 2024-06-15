#include <bits/stdc++.h>
using namespace std;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;

    vector<int> dp(n+10, 10000000), a(n);

    for(int i = 0; i < n; i++) cin >> a[i];
    
    dp[0] = 0; // there are 0 ways to have sum 0.

    for(int i = 1; i <= c; i++){
        for(int j = 0; j < n; j++){//testing the coins.
            if(i - a[j] >= 0) dp[i] = min(dp[i], dp[i - a[j]] + 1);
        }
    }
    
    if(dp[c] == 10000000) dp[c] = -1;
    cout << dp[c] << "\n";

    return 0;
}