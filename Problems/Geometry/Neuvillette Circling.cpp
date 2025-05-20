#include <bits/stdc++.h>
using namespace std;

#pragma region

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
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
 
template<class T> using ordset = tree<T, null_type, less<T>,
rb_tree_tag, tree_order_statistics_node_update>;
 
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

using T = double;

typedef pair<T,T> pt;
typedef pair<pt,T> circle;
typedef vector<pt> vpt;
 
const T EPS = 1e-8;
 
int sgn(T a) {return (a>EPS)-(a<-EPS);}
 
pt operator-(pt a) {return make_pair(-a.ft, -a.sd);}
pt &operator+=(pt &a, pt b) {
    a.ft += b.ft;
    a.sd += b.sd;
    return a;
}
 
pt &operator-=(pt &a, pt b) {
    a.ft -= b.ft;
    a.sd -= b.sd;
    return a;
}
 
pt &operator*=(pt &a, T r) {
    a.ft *= r;
    a.sd *= r;
    return a;
}
 
pt &operator/=(pt &a, T r) {
    a.ft /= r;
    a.sd /= r;
    return a;
}
 
pt operator+(pt a, pt b) {return a += b;}
pt operator-(pt a, pt b) {return a -= b;}
pt operator*(pt a, T r) {return a *= r;}
pt operator/(pt a, T r) {return a /= r;}
T sq(T a) {return a*a;}
T abs2(pt p) {return sq(p.ft)+sq(p.sd);}
T abs(pt p) {return sqrtl(abs2(p));}
pt conj(pt p) {return make_pair(p.ft, -p.sd);}
 
pt operator*(pt a, pt b) {return pt(a.ft*b.ft-a.sd*b.sd, a.sd*b.ft+a.ft*b.sd);}
pt operator/(pt a, pt b) {return a*conj(b)/abs2(b);}
 
int in(const circle& x, const pt& y) {
    return sgn(abs(y-x.first)-x.second);
}
 
circle ccCenter(pt a, pt b, pt c) {
    b -= a;
    c -= a;
    pt res = b*c*(conj(c)-conj(b))/(b*conj(c)-conj(b)*c);
    return {a+res, abs(res)};
}

const T inf = 1e9;

void test(){

    /*
      A ideia desse problema é: podemos precalcular, para cada quantidade de pontos em um círculo, qual a menor área de um círculo que inclue esses pontos.
      Para montar um círculo, temos a seguinte observação: Podemos montá-lo com 2 ou 3 pontos, e podemos garantir que montar eles dessa forma gera o círculo
      ótimo. Assim, podemos apenas calcular a área do círculo formado com 2 ou 3 pontos e resolver para cada quantidade de pontos que queremos dentro dele.

      A complexidade de testar todos os N pontos, tomados 3 a 3 é O(n^3), e para saber quais pontos estão no círculo centrado em um ponto P com área A é O(n), 
      pois preciso testar para cada ponto se ele está dentro desse círculo. Portanto, o algoritmo todo roda em O(n^4), o que está ok com o tempo.
    */
  
    int n;
    cin >> n;

    vpt a(n);
    for(int i=0; i<n; i++){
        cin>>a[i].ft>>a[i].sd;
    }

    auto md = [&](pt x, pt y) {
        return (x+y)/2.0;
    };
    
    vector<T> rs(n*n, inf);
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            T tmp = abs(a[i]-a[j])/2.0;
            int ct = 2;
            for(int k=0; k<n; k++){
                if(k==i || k==j) continue;
                if(in(circle(md(a[i],a[j]), tmp), a[k]) <= 0) {
                    ct++;
                }
            }
            rs[ct*(ct-1)/2] = min(rs[ct*(ct-1)/2], tmp);
        }
    }


    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                auto x = ccCenter(a[i],a[j],a[k]);
                int ct=3;
                for(int l=0; l<n; l++){
                    if(l == i || l == j || l == k) continue;
                    if(in(x,a[l]) <= 0) ct++;
                }
                rs[ct*(ct-1)/2]=min(rs[ct*(ct-1)/2], x.sd);
            }
        }
    }

    for(int i=1; i<n; i++){
        for(int j=0; j<i; j++){
            cout<<rs[i*(i+1)/2]<<"\n";
        }
    }
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(8);
    
    int tt = 1;
    // cin >> tt;
 
    for(int i=1; i<=tt; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
