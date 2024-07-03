////
// https://codeforces.com/edu/course/2/lesson/6/4/practice/contest/285069/problem/C
////

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

    vector<double> a, b;

    for(int i = 0; i < n; i++){
        string s, t;
        cin >> s >> t;
        a.pb(stod(s));
        b.pb(stod(t));
    }

    auto f = [&](double x){
        vector<double> vals;
        for(int i = 0; i < n; i++){
            vals.pb(a[i] - b[i]*x);
        }
        sort(all(vals));
        reverse(all(vals));

        double rs = 0;
        for(int i = 0; i < k; i++){
            rs += vals[i];
        }

        return rs > 0.0;
    };

    double l = 0, r = 1e5;

    for(int g = 0; g < 50; g++){
        double mid = (l+r)/2;
        if(f(mid)) l = mid;
        else r = mid;
    }

    cout << l << "\n";

    return 0;
}
