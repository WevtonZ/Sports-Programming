#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9+7;

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> grid(n);
    for(int i = 0; i < n; i++) cin >> grid[i];

    vector<vector<int>> dp(n+1, vector<int>(n+1));

    dp[0][0] = grid[0][0] == '.';

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == '.'){
                if(i > 0 && grid[i-1][j] == '.')
                    dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
                if(j > 0 && grid[i][j-1] == '.') 
                    dp[i][j] = (dp[i][j] + dp[i][j-1]) % mod;
            }
        }
    }

    cout << dp[n-1][n-1] << "\n";

    return 0;
}