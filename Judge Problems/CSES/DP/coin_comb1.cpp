#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c;
    cin >> n >> c;

    vector<int> dp(c+1, 0), a(n);

    for(int i = 0; i < n; i++) cin >> a[i];

    dp[0] = 1; // one way to form sum 0. Take nothing and there we go.

    for(int i = 1; i <= c; i++){
        for(int j = 0; j < n; j++){
            if(i - a[j] >= 0){
                dp[i] = (dp[i] + dp[i-a[j]]) % mod;
            }
        }
    }

    cout << dp[c] << "\n";
    
    return 0;
}