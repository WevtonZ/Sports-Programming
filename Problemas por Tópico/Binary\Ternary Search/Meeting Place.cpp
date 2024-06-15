// https://codeforces.com/contest/782/problem/B

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define all(x) x.begin(), x.end()

const ll mod = 1e9+7;

vector<ld> a, b;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        a.push_back(stod(s));
    }

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        b.push_back(stod(s));
    }

    ld ans = 36;

    ld l = 0, r = 1e9;

    for(int i = 0; i < 90; i++){
        ld mid = (l+r)/2.0;

        ld inter1 = mod, inter2 = -mod;
        for(int j = 0; j < n; j++){
            inter1 = min(inter1, a[j] + b[j]*mid);
            inter2 = max(inter2, a[j] - b[j]*mid);
        }

        if(inter1 < inter2){
            l = mid;
        }
        else{
            r = mid;
            ans = mid;
        }
    }

    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}
