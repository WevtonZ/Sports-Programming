// String Matching - CSES Solution
// link: https://cses.fi/problemset/task/1753

/*
    Classic pattern matching problem. The idea is that you can do string matching using the
    prefix of the string. When the problem is to find a pattern that comes from other string,
    you can concatenate them and reduces to string matching of the prefix.
    There is a lot of algorithms that can find those fast. This one uses Z-Function. O(N) Complexity.
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+10;

int z[N];

void z_function(const string & s){
    int n = s.size();
    int l = 0, r = 0;
    for(int i = 1; i < n; i++){
        if(i < r){
            z[i] = min(z[i-l], r-i);
        }
        while(i < n && s[z[i]] == s[i+z[i]])
            z[i]++;
        
        if(i + z[i] > r){
            l = i;
            r = i+z[i];
        }
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;
    s = t + '$' + s;
    z_function(s);

    int ans = 0;
    
    for(int i = 0; i < s.size(); i++){
        if(z[i] == t.size()){
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}