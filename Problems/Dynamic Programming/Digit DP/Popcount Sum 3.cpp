// https://atcoder.jp/contests/abc406/tasks/abc406_e

#include <bits/stdc++.h>
using namespace std;

#pragma region

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define eb emplace_back
#define pb push_back
#define get_bit(x,i) ((x)&(1ll<<(i)))

using ll = long long;
using ld = long double;
using i128 = __int128_t;
 
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

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const int MOD = 998244353;

struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD;}
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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int N = 62;

pair<ll,mi> dp[N][N][2];
char vis[N][N][2];
ll n, k;
int cor = 1;

vector<int> bit;

/*
    Vamos pensar em como contar quantos números temos, de 1 a N, com exatamente K bits em sua
    representação binária. Vamos construir uma Programação Dinâmica com as seguintes características

    dp[cara_atual, quantidade_de_bits, é_menor].

    Como casos base, temos que:
    
    1. Se a quantidade de bits for maior que K, retornamos 0, já que estouramos a quantidade de
    bits válida.
    2. Se at == L, com L sendo o tamanho da representação binária de N, verificamos:    
        2.1. Se a quantidade de bits atual for K, retornamos 1. Senão, retornamos 0.

    3. Se já visitamos esse estado, retornamos o valor dele (memoização).

    Agora, para as transições, temos:

    1. Olhamos para o bit atual e vemos se o cara é menor ou não que o bit atual, pois a partir
    daqui temos dois tipos de solves quando isso acontece.

    2. Para cada cara, apenas retornamos o solve do próximo, pois a partir daqui, podemos contar
    quantos bits no sufixo da dp podemos combinar com os bits atuais.

    Com isso, resolvemos o problema de contar quantos números tem exatamente K bits na sua
    representação binária.

    Podemos estender essa ideia para conseguir somar o valor de cada cara se olharmos cada bit
    separadamente. Na mesma contagem de bits, podemos também usar eles para somar o valor que esse
    bit tem na soma final. É necessário fazer alguma verificações, mas ainda é possível fazer
    isso na mesma complexidade de contar quantos números tem K bits.

    A complexidade dessa solução é O(60*60*2*2).
*/

pair<ll,mi> solve(int at, int kk, bool is_less) {
    if(kk > k) return make_pair(0, 0);
    if(at == bit.size()){
        if(kk == k) return make_pair(1, 0);
        return make_pair(0, 0);
    }

    if(vis[at][kk][is_less] == cor) return dp[at][kk][is_less];
    vis[at][kk][is_less] = cor;

    mi sum = 0;
    ll cnt = 0;

    int lim = is_less ? 1 : bit[at];
    for(int i=0; i<=lim; i++) {
        auto tmp = solve(at+1, kk+i, is_less || (i < bit[at]));
        if(tmp.ft == 0) continue;

        cnt += tmp.ft;

        mi curr_bit = mi(i * mi(1ll << (bit.size()-1-at)));
        mi curr_sum = curr_bit * tmp.ft;
        
        sum += tmp.sd + curr_sum;
    }

    return dp[at][kk][is_less] = make_pair(cnt, sum);
}

void test(){
    cin >> n >> k;
    bit.clear();
    
    for(int i=0; i<61; i++){
        int b = (n & (1ll << i)) > 0;
        bit.pb(b);
    }
    reverse(all(bit));

    auto rs = solve(0, 0, 0);
    cout << rs.sd.v << "\n";
    cor++;
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(8);

    int tt = 1;
    cin >> tt;
 
    for(int i=1; i<=tt; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
