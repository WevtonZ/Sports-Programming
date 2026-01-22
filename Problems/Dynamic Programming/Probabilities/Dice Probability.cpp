// https://cses.fi/problemset/task/1725

#include <bits/stdc++.h>
using namespace std;
 
#pragma region
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
 
#define int long long
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
 
#pragma endregion
 
const int mod = 1e9+7;
 
int n, a, b;
double dp[110][610];
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout<<fixed<<setprecision(6);
 
    cin >> n >> a >> b;
 
    dp[0][0] = 1.0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= 6*n; j++){
            for(int k = 1; k <= 6; k++){
                if(j - k >= 0){
                    dp[i][j] += dp[i-1][j-k];
                }
            }
 
            dp[i][j] /= 6.0;
        }
    }
 
    double ans = 0;
    for(int i = a; i <= b; i++){
        ans += dp[n][i];
    }
 
    cout << ans << "\n";
 
    return 0;
}
