//Finding Periods - CSES Solution
// link: https://cses.fi/problemset/task/1733

/*
    Periods are defined as a prefix that is used to generate the string. By using Z-Function,
    one can just modify the algorithm to see if z[i] + i == n.
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

        if(z[i] + i == n)
            cout << i << " ";
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    z_function(s);
    cout << s.size() << "\n";

    return 0;
}