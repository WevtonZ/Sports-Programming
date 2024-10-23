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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MOD = 1e9+7;
 
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

const int N = 110;

ld dp[N][N][N];
char vis[N][N][N];

ld solve(int r, int s, int p) { // podemos resolver apenas para pedra, e colocar os caras corretos lá na resposta.
    if(r && !s && !p) return 1.0; // quando o jogo termina e pedra é o único que sobra.
    if(vis[r][s][p]) return dp[r][s][p];
    vis[r][s][p]=1;
    dp[r][s][p]=0;

    int ways = r*s + r*p + s*p; // numero de maneiras de pegar algum desses pares.

    // p ganha de r. Preciso manter pelomenos uma pedra no jogo.
    if(r > 1 && p > 0) dp[r][s][p] += (ld(r*p) / ld(ways)) * solve(r-1, s, p);

    // r ganha de s.
    // aqui eh tipo, se eu tenho pedras e quero que ela ganhe. Não pode acabar a qtd de tesouras, a menos que não tenha mais papel.
    if(r > 0 && (s > 1 || (s > 0 && p == 0))) dp[r][s][p] += (ld(r*s) / ld(ways)) * solve(r, s-1, p);

    // s ganha de p.
    // necessário acabar com os papéis.
    if(s > 0 && p > 0) dp[r][s][p] += (ld(s*p) / ld(ways)) * solve(r, s, p-1);
    return dp[r][s][p];
}

void test() {
    int r, s, p;
    cin >> r >> s >> p;
    cout << solve(r, s, p) << " " << solve(s, p, r) << " " << solve(p, r, s) << "\n";    
} 
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(15);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case #"<<i<<": ";
        test();
    }
    
    return 0;
}
