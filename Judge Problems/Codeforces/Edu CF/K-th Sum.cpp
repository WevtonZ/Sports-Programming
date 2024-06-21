// https://codeforces.com/edu/course/2/lesson/6/5/practice/contest/285084/problem/C

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()

#define int long long
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const int N = 1e5+10;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(12);

    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);

    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    for(int i = 0; i < n; i++)
        cin >> b[i];
    
    // sort(all(a));
    sort(all(b));

    auto f = [&](int x){
        int cnt = 0;

        for(int i = 0; i < n; i++){
            int j = upper_bound(all(b), x-a[i]) - b.begin();
            cnt += j;
        }
        // cout<<"x: "<<x<<" cnt: "<<cnt<<"\n";
        return cnt >= k;
    };

    int l = 1, r = 2e9+1, rs = 0;

    while(l <= r){
        int mid = (l+r)/2;
        if(f(mid)){
            r = mid-1;
            rs = mid;
        }
        else
            l = mid+1;
    }

    cout << rs << "\n";

    return 0;
}
