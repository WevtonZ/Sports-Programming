// https://codeforces.com/gym/103960/problem/F

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(0);

    map<string,int> M;

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        string s; cin >> s;
        int id=0;
        for(int j = 0; j < s.size(); j++){
            if(s[j]=='*'){
                id=j;
                break;
            }
        }

        for(char c = 'a'; c <= 'z'; c++){
            s[id]=c;
            M[s]++;
        }
    }

    int mx=0;
    string rs;

    for(auto [str, ct]: M){
        if(ct>mx){
            mx=ct;
            rs=str;
        }
        else if(ct==mx){
            rs=min(rs,str);
        }
    }

    cout<<rs<<" "<<mx<<"\n";

    return 0;
}
