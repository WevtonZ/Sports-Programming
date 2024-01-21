#include <bits/stdc++.h>
using namespace std;

#define int long long

const int inf = -1e5;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, W;
    cin >> n >> W;
    vector<int> c(n), w(n);

    for(int i = 0; i < n; i++) cin >> c[i];
    for(int i = 0; i < n; i++) cin >> w[i];

    vector<vector<int>> dp(W+1, vector<int>(2, inf));
    dp[W][0] = 0;
    bool flag = false;
    for(int i = 0; i < n; i++){
        flag ^= 1;
        for(int j = W; j >= 0; j--){
            dp[j][flag] = dp[j][flag^1];
            if(j + c[i] > W || dp[j + c[i]][flag^1] == inf) continue;
            dp[j][flag] = max(dp[j][flag], dp[j+c[i]][flag^1] + w[i]);
        }
    }

    int ans = 0;
    for(int i = 0; i <= W; i++) ans = max(ans, dp[i][flag]);
    cout << ans << "\n";

    return 0;
}