// https://codeforces.com/contest/1165/problem/E

/*
    Em problemas de contribuição, a ideia é fixar alguma coisa e contar quantas vezes aquela coisa aparece na resposta.
    No nosso caso, fixaremos o produto a_i * b_i e veremos quantas vezes cada cara aparece na resposta. No final, cada um desses caras vai aparecer
    i*(n-i+1) vezes, para todo 1 <= i <= n. Como o a_i é fixo e só o b_i pode variar, temos que o produto a_i * i * (n-i+1) também é fixo, e agora o negócio é achar
    qual o valor de b_i que minimiza o somatório. Para minimizar um produto de dois caras, eles tem que estar o mais distante possível, então podemos parear os números
    de tal forma que os maiores valores de a se juntem com os menores valores de b, e isso garante que o somatório seja mínimo.
*/

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
 
#define rep(i, begin, end) for(__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2*((begin) > (end)))
 
// using i128 = __int128_t;
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdb = pair<ld,ld>;

// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
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

const int MOD = 998244353;

struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi &operator+=(mi &a, mi b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
mi &operator-=(mi &a, mi b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v * b.v); }
mi &operator*=(mi &a, mi b) { return a = a * b; }
mi mypow(mi a, long long p) {
    assert(p >= 0);
    return p == 0 ? 1 : mypow(a * a, p / 2) * (p & 1 ? a : 1);
}
mi inv(mi a) {
    assert(a.v != 0);
    return mypow(a, MOD - 2);
}
mi operator/(mi a, mi b) { return a * inv(b); }

#pragma endregion

const int N = 1e6+10;

void test() {
    int n;
    cin >> n;
    vector<ll> a;
    for(int i=0; i<n; i++){
        ll x;
        cin >> x;
        a.pb(x*1ll*(i+1)*(n-i));
    }
    vector<ll> b(n);
    for(int i=0; i<n; i++) cin>>b[i];
    sort(all(a));
    sort(all(b));
    reverse(all(a));

    mi rs = 0;
    for(int i=0; i<n; i++){
        rs = rs + (mi(a[i])*mi(b[i]));
    }
    cout<<rs.v<<"\n";
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);

    int t = 1;
    // cin >> t;

    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
