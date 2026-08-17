// https://codeforces.com/gym/106636/problem/H

#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(x, i) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

// ordenar antes de usar essa funcao
#define make_unique(x) x.erase(unique(x.begin(), x.end()), x.end())

using ll = long long;
using ld = long double;
using ull = unsigned int;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAGIC = 250;

void test() {
    int n, q;
    cin >> n >> q;

    vector<ll> a(n+1);
    for(int i=1; i<=n; i++) cin >> a[i];
    vector<vector<ll>> pref(n+1, vector<ll>(MAGIC, 0));

    for(int j=1; j<MAGIC; j++){
        for(int i=1; i<=n; i++){
            if(i-j>=0) pref[i][j]=pref[i-j][j]+a[i];
            else pref[i][j]=a[i];
        }
    }

    // for(int j=1; j<=n; j++){
    //     for(int i=1; i<=n; i++) cout<<pref[i][j]<<" ";
    //     cout<<el;
    // }

    while(q--){
        int l, r, x, m;
        cin >> l >> r >> x >> m;
        // fazer umas contas pra achar o cara certo
        if(m<MAGIC){
            int nl=l, nr=r;
            if(l%m < x%m){
                nl += x-(l%m);
            }
            else if(l%m > x%m){
                nl+=m-(l%m);
                nl+=x;
            }
    
            if(r%m > x){
                nr-=((r%m)-x);
            }
            else if(r%m < x){
                nr-=(r%m);
                nr-=(m-x);
            }
    
            if(nl>=l && nl<=r && nr>=l && nr<=r){
                // dbg(nl);
                // dbg(nr);
                // dbg(m);
                // dbg(pref[nr][m]);
                // dbg(pref[max(0,nl-m)][m]);
                cout<<pref[nr][m]-pref[max(0,nl-m)][m]<<el;
            }
            else{
                cout<<"0"<<el;
            }
        }
        else{
            int nl = l;
            if(l%m < x%m){
                nl += x-(l%m);
            }
            else if(l%m > x%m){
                nl+=m-(l%m);
                nl+=x;
            }
            ll rs = 0;
            while(nl<=r){
                rs+=a[nl];
                nl+=m;
            }
            cout<<rs<<el;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
