// https://codeforces.com/gym/104555/problem/I

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

    ll rs=0;

    map<int,int> M;
    M[0]=1;
    int sum=0;
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        sum ^= x;
        rs += M[sum^1];
        M[sum]++;
    }

    cout<<rs<<"\n";

    return 0;
}
