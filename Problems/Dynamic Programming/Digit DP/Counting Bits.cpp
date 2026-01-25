// https://cses.fi/problemset/task/1146/

#include <bits/stdc++.h>
using namespace std;
 
#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
 
using ll = long long;
using ld = long double;
 
// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T, typename T1> ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1> istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#pragma endregion
 
const int N = 52;
 
ll dp[N][2][N];
 
string s;
 
ll solve(int at, int ok, int qtd) {
    if(at == s.size()) return qtd;
    ll &rs = dp[at][ok][qtd];
 
    if(rs != -1) return rs;
    rs = 0;
 
    if(!ok) {
        for(int i=0; i<=s[at]-'0'; i++) {
            rs += solve(at+1, i < s[at]-'0', qtd+i);
        }
    }
    else{
        for(int i=0; i<=1; i++){
            rs += solve(at+1, ok, qtd+i);
        }
    }
    return rs;
}
 
void test() {
    ll n;
    cin >> n;
    memset(dp, -1, sizeof dp);
    bitset<N> x(n);
    for(int i=0; i<N; i++) {
        s.pb(x[i]+'0');
    }
    reverse(all(s));
 
    cout << solve(0, 0, 0) << "\n";
}
 
int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(1);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
