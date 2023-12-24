#include <bits/stdc++.h>
using namespace std;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    int ans = 1;
    while(n >= 10){
        s = to_string(n);
        int v = 0;
        for(int i = 0; i < s.size(); i++){
            v = max(v, s[i]-'0');
        }
        n -= v;
        ans++;
    }

    cout << ans << "\n";
    
    return 0;
}