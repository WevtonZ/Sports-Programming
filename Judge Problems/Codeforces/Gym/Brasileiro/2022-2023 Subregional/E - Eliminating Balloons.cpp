// https://codeforces.com/gym/103960/problem/E

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

    int n;
    cin >> n;

    multiset<int> S;
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        S.insert(x);
        if(S.find(x+1) != S.end()){
            S.erase(S.find(x+1));
        }
    }

    cout<<S.size()<<"\n";

    return 0;
}
