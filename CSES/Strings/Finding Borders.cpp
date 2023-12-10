// Finding Borders - CSES Solution
// link: https://cses.fi/problemset/task/1732

/*
    Finding all the borders of the string means when a string is equal in its prefix and suffix.
    This can be done using a Z-Function or using String Hashing. Knowing the Z of every character,
    one can just see if i + z[i] = |S|, because if that is true, then this means that the prefix
    and suffix of the string are equal.
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
            z[i] = min(r - i, z[i-l]);
        }

        while(i < n && s[z[i]] == s[i+z[i]]){
            z[i]++;
        }

        if(i + z[i] > r){
            l = i;
            r = i+z[i];
        }
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    z_function(s);
    int n = s.size();

    for(int i = n-1; i >= 0; i--){
        if(i + z[i] == n){
            cout << z[i] << " ";
        }
    }

    cout << "\n";

    return 0;
}