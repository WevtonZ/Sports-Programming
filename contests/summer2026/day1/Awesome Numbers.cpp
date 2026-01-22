#include <bits/stdc++.h>
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1ll << (i)) & (x)) // testar bit i no valor x
#define mp make_pair
#define mt make_tuple
#define dbg(x) cout << #x << " = " << x << endl;

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

// template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

void test() {
    ll l, r;
    cin >> l >> r;
    if(l <= 5 && 5 <= r) cout<<"1\n";
    else cout<<"0\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    // sieve();

    int tt=1;
    cin >> tt;
    
    for(int _=1; _<=tt; _++) {
        // cout<<"Case #"<<_<<": ";
        test();
        // if(_<tt) cout<<"\n";
    }
    
    return 0;
}
