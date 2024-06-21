// https://cses.fi/problemset/task/2217

#include<bits/stdc++.h>
using namespace std;
 
//template
#pragma region
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
// #pragma GCC optimize("O3", "unroll-loops") // for fast N^2
// #pragma GCC target("avx2", "popcnt") // for fast popcount
// some macros
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define mt make_tuple
#define mp make_pair
#define eb emplace_back
#define pb push_back
// loop that goes (begin,..,end]
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
 
typedef long long ll;
typedef __int128_t lll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;
 
// ordered set
template<class T> using ordset = tree<int, 
                        null_type, less<T>, 
                        rb_tree_tag, tree_order_statistics_node_update>;
 
//read and print pair
template<typename T>
ostream& operator<<(ostream& os, pair<T, T> p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
 
template<typename T>
istream& operator>>(istream& is, pair<T, T> &p) {
    is >> p.first >> p.second;
    return is;
}
 
//error debug
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
 
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion
 
const int N = 2e6+10;
const ll inf = 1e9+9;
 
vector<int> a, b, mark;
 
void test(){
    int n, q;
    cin >> n >> q;
    a.resize(n+10);
    b.resize(n+10);
    mark.assign(n+10, inf);
    mark[0] = 0;
    rep(i,1,n+1){
        cin >> a[i];
        b[a[i]] = i;
    }
 
    int ans = 1;
    rep(i,2,n+1){
        if(b[i] < b[i-1]){
            ans++;
            mark[i-1]=1;
        }
        else{
            mark[i-1]=0;
        }
    }
 
    while(q--){
        set<int> S;
        int x, y;
        cin >> x >> y;
        
        if(x>y){
            swap(x,y);
        }
 
        S.insert(a[x]);
        S.insert(a[x]-1);
        S.insert(a[y]);
        S.insert(a[y]-1);
 
        swap(b[a[x]], b[a[y]]);
        swap(a[x], a[y]);
 
        for(auto i: S){
            // cout << i << ' ' << i+1 << '\n';
            // cout << "b: ";
            // cout << b[i] << ' ' << b[i+1] << '\n';
            if(b[i] > b[i+1] && !mark[i]){
                ans++;
                mark[i] ^= 1;
            }
            else if(b[i] < b[i+1] && mark[i]){
                ans--;
                mark[i] ^= 1;
            }
        }
        cout << ans << '\n';
 
    }
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
    // cin >> teste;
 
    while(teste--){
        test();
    }
    
    return 0;
}
