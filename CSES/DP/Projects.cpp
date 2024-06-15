// https://cses.fi/problemset/task/1140

// all I know about this problem was that it was based on some interval problem on some paper, but it is
// a very straighfoward problem on DP Optimization, where you need to find what is the best previous state
// to jump from. In this case, since the DP array is non-decreasing, one can just Binary Search the previous
// non overlapping segment to the actual one and use it as an answer.

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
 
#define int long long
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
 
const int N = 2e5+10;
 
int dp[N];
 
struct Data{
    int l, r, val;
};
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(12);
 
    int n;
    cin >> n;
    vector<Data> a(n+1);
 
    for(int i = 1; i <= n; i++){
        cin >> a[i].l >> a[i].r >> a[i].val;
    }
 
    auto cmp = [&] (const Data x, const Data y){
        return x.r < y.r;
    };
 
    sort(all(a), cmp);
    vector<int> dist(n+1);
    for(int i = 1; i <= n; i++){
        dist[i] = a[i].r;
    }
 
    for(int i = 1; i <= n; i++){
        int j = lower_bound(all(dist), a[i].l) - dist.begin();
        // cout<<a[j].r<<" "<<a[i].l<<"\n";
        // if(a[j].r >= a[i].l) j--;
        dp[i] = max(dp[i-1], dp[j-1] + a[i].val);
        // cout<<j-1<<"\n";
    }
 
    cout << dp[n] << "\n";
 
    return 0;
}
