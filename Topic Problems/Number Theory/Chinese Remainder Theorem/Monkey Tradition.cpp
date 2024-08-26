// https://lightoj.com/problem/monkey-tradition

/*
  Esse problema eh uma aplicação direta do Teorema Chines do Resto para várias equações. Como tudo eh primo, podemos fazer e sempre haverá uma resposta válida.
  
*/

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
 
#define rep(i, begin, end) for(__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2*((begin) > (end)))
 
using i128 = __int128_t;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdb;
 
template <typename T, typename T1>
ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1>
istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}

ll gcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x=1;
        y=0;
        return a;
    }

    ll x0, y0;
    ll g = gcd(b, a%b, x0, y0);
    x = y0;
    y = x0-y0*(a/b);
    return g;
}

void test() {
    int n;
    cin >> n;
    vector<int> p(n), r(n);
    for(int i=0; i<n; i++){
        cin >> p[i] >> r[i];
    }

    ll a1 = r[0], m1 = p[0];
    for(int i=1; i<n; i++){
        ll a2 = r[i], m2 = p[i];
        ll x, y;
        gcd(m1, m2, x, y);
        ll rs = i128(a1)*y*m2%(m1*m2) + i128(a2)*x*m1%(m1*m2);
        m1 *= m2;
        a1 = rs%m1;
        if(a1<0) a1 += m1;
    }
    cout << a1 << "\n";
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);

    int t = 1;
    cin >> t;

    for(int i=1; i<=t; i++){
        cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
