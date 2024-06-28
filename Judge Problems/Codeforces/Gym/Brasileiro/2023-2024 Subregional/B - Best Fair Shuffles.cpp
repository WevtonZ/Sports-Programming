// https://codeforces.com/gym/104555/problem/B

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

const int N = 1e5+5;
const ll inf = 1e16;

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> a(n+1), b(n+1);
    for(int i = 1; i <= n; i++)
        cin >> a[i], b[a[i]] = i;
    
    int rs=0;
    for(int i = 1; i < n; i++){
        if(b[i]>b[i+1]) rs++;
    }

    ll po = 1, cnt=0;
    while(po<=rs) po*=2, cnt++;
    cout<<cnt<<"\n";

    return 0;
}
