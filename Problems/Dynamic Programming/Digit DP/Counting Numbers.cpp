// https://cses.fi/problemset/task/2220/

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
 
#define int long long
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
 
int dp[20][11][2][2];
int a, b;
int n;
string s;
 
int solve(int at, int d, bool is_0, bool ok){
    if(at == n){
        return 1;
    }
    int &ans = dp[at][d][is_0][ok];
    if(ans != -1) return ans;
    ans = 0;
 
    if(ok){
        for(int i = 0; i <= 9; i++){
            if(i == d && !is_0) continue;
            ans += solve(at+1, i, (is_0 && (i == 0)), ok);
        }
    }
    else{
        for(int i = 0; i <= s[at]-'0'; i++){
            if(i == d && !is_0) continue;
            ans += solve(at+1, i, (is_0 && (i == 0)), i < (s[at]-'0'));
        }
    }
 
    return ans;
}
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    // cout<<fixed<<setprecision(6);
 
    cin >> a >> b;
    s = to_string(b);
    int ans, ans2;
    ans = ans2 = 0;
    memset(dp, -1, sizeof(dp));
    n = s.size();
    ans = solve(0, 10, 1, 0);
    memset(dp, -1, sizeof(dp));
    s = to_string(a-1);
    n = s.size();
    ans2 = solve(0, 10, 1, 0);
    cout << ans - ans2 << "\n";
 
    return 0;
}
