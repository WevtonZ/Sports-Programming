#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(i, x) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

using ll = long long;
using ld = long double;
 
template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void test() {
    
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(6);
 
    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
