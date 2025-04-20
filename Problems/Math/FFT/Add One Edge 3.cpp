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
// using i128 = __int128_t;
 
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

const int MOD = 1e9+7;

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

const int N = 2e5+10;

vector<vector<int>> g1, g2;

int x, d;

void dfs_dist(int u, int ant, const vector<vector<int>> & graph, vector<vector<int>> & dist, int id) {
    if(dist[u][id] > d){
        d = dist[u][id];
        x = u;
    }

    for(auto v: graph[u]){
        if(v == ant) continue;
        dist[v][id] = dist[u][id]+1;
        dfs_dist(v,u,graph,dist,id);
    }
}

/*
  Template de FFT do Felipe Sabino, pega do KACTL, sem a NTT pq eu n sei o que é isso.
  Não vou explicar aqui o que o código faz porque é meio complexo, e também não precisa saber o que ele faz, mas
  precisa saber o que ele te retorna quando usado.

  Você passa dois vetores pra ele, e ele te retorna um outro vetor que é a convolução dos vetores passados.
  Convolução no nosso caso é apenas uma multiplicação dos polinômios. Algoritmo roda em O((n+m)log(n+m)).

  Código original: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h
*/

struct FFT{
    typedef complex<double> C;
    typedef vector<double> vd;
    typedef vector<long long int> vl;
    typedef vector<int> vi;

    void fft(vector<C>& a) {
        int n = a.size(), L = 31 - __builtin_clz(n);
        static vector<complex<long double>> R(2, 1);
        static vector<C> rt(2, 1);  // (^ 10% faster if double)
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n); rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            for(int i=k; i<2*k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
        }
        vi rev(n);
        for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for(int i = 0; i < n; i++)  if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k) for(int j = 0; j < k; j++) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
                C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
    }

    /*
    	Função que multiplica dois polinômios. Em double e em int, caso alguém queria diferenciar
     	a vida.
    */
    vd conv(const vd& a, const vd& b) {
        if (a.empty() || b.empty()) return {};
        vd res(a.size() + b.size() - 1);
        int L = 32 - __builtin_clz(res.size()), n = 1 << L;
        vector<C> in(n), out(n);
        copy(a.begin(),a.end(), in.begin());
        for(int i = 0; i < b.size(); i++) in[i].imag(b[i]);
        fft(in);
        for (C& x : in) x *= x;
        for(int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
        fft(out);
        for(int i = 0; i < res.size(); i++) res[i] = imag(out[i]) / (4 * n);
        return res;
    }
    vl conv(const vl& a, const vl& b) {
        if (a.empty() || b.empty()) return {};
        vl res(a.size() + b.size() - 1);
        int L = 32 - __builtin_clz(res.size()), n = 1 << L;
        vector<C> in(n), out(n);
        copy(a.begin(),a.end(), in.begin());
        for(int i = 0; i < b.size(); i++) in[i].imag(b[i]);
        fft(in);
        for (C& x : in) x *= x;
        for(int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
        fft(out);
        for(int i = 0; i < res.size(); i++) res[i] = round(imag(out[i]) / (4 * n));
        return res;
    }

    /*
    	Multiplica dois polinômios modulo M, sendo M um inteiro qualquer.
     	Tem maior precisão do que usar double pra multiplicar polinômios, vai a gosto do freguês.
    */
    template<int M> vl convMod(const vl &a, const vl &b) {
        if (a.empty() || b.empty()) return {};
        vl res(a.size() + b.size() - 1);
        int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(sqrt(M));
        vector<C> L(n), R(n), outs(n), outl(n);
        for(int i = 0; i < a.size(); i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
        for(int i = 0; i < b.size(); i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
        fft(L), fft(R);
        for(int i = 0; i < n; i++) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        fft(outl), fft(outs);
        for(int i = 0; i < res.size(); i++) {
            ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
            ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
};

void test(){
    int n1, n2;
    cin >> n1;

    g1.resize(n1+1);

    for(int i=1; i<n1; i++){
        int u,v;
        cin >> u >> v;
        g1[u].pb(v);
        g1[v].pb(u);
    }

    cin >> n2;
    g2.resize(n2+1);

    for(int i=1; i<n2; i++){
        int u, v;
        cin >> u >> v;
        g2[u].pb(v);
        g2[v].pb(u);
    }

    vector<vector<int>> d1(n1+1, vector<int>(2,0)), d2(n2+1, vector<int>(2, 0));

    dfs_dist(1,1,g1,d1,0);
    d=0;
    d1[x][0]=0;
    dfs_dist(x,x,g1,d1,0);
    d=0;
    dfs_dist(x,x,g1,d1,1);
    d=0;

    dfs_dist(1,1,g2,d2,0);
    d=0;
    d2[x][0]=0;
    dfs_dist(x,x,g2,d2,0);
    d=0;
    dfs_dist(x,x,g2,d2,1);
    d=0;

    vector<ll> f1(N, 0);
    vector<ll> f2(N, 0);

    ll di1, di2;
    di1=di2=0;

    for(int i=1; i<=n1; i++){
        int tmp = max(d1[i][0], d1[i][1])+1;
        di1=max<ll>(di1,tmp-1);
        f1[tmp]++;
    }
    for(int i=1; i<=n2; i++){
        int tmp = max(d2[i][0], d2[i][1]);
        di2=max<ll>(di2,tmp);
        f2[tmp]++;
    }

    FFT f;
    auto g = f.conv(f1, f2);
    ll rs = 0;
    for(int i=0; i<g.size(); i++) {
        if(g[i]){
            ll tmp = max<ll>({i, di1, di2});
            rs+=g[i]*tmp;
        }
    }
    cout<<rs<<"\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
    
    int tt = 1;
    // cin >> tt;
 
    for(int i=1; i<=tt; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
