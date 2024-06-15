// Dice Combinations - CSES Solution

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> dp;

    int n;
    cin >> n;

    dp.resize(n+1, 0);
    dp[0] = 1; // I have one combination with zero dices.

    // combination of others is the sum of the previous combinations.
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 6; j++){
            if(i - j >= 0) dp[i] = (dp[i] + dp[i-j]) % mod;
        }
    }

    cout << dp[n] << "\n";
    
    return 0;
}