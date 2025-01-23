// https://codeforces.com/gym/105669/problem/D2

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int mod = 1e9+7;
const int N = 1e5+10;

ll fat[N], ifat[N];

ll fexp(ll a, ll b) {
    ll rs=1;
    while(b){
        if(1&b) rs=rs*a%mod;
        a = a*a%mod;
        b>>=1;
    }
    return rs;
}

void _set() {
    fat[0]=1;
    for(int i=1; i<N; i++){
        fat[i] = fat[i-1]*i%mod;
    }
    ifat[N-1] = fexp(fat[N-1], mod-2);
    for(ll i=N-2; i>=0; i--){
        ifat[i] = (i+1)*ifat[i+1]%mod;
    }
}

ll comb(ll n, ll k) {
    if(k > n) return 0;
    ll rs = fat[n];
    rs = rs * ifat[k] % mod * ifat[n-k] % mod;
    return rs;
}

using cd = complex<double>;
const double PI = acos(-1);

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
        for(int i=k; i<2*k; i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for(int i=0; i<n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i=0; i<n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for(int j=0; j<k; j++) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(a.size() + b.size() - 1);
	int L = 32 - __builtin_clz(res.size()), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	for(int i=0; i<b.size(); i++) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	for(int i=0; i<n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for(int i=0; i<res.size(); i++) res[i] = imag(out[i]) / (4 * n);
	return res;
}

template<int M> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};
	vector<ll> res(a.size() + b.size() - 1);
	int B=32-__builtin_clz(res.size()), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	for(int i=0; i<a.size(); i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	for(int i=0; i<b.size(); i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	for(int i=0; i<n; i++) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for(int i=0; i<res.size(); i++) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

void test() {
    /*
    Basicamente a gente precisa contar, para cada N, quantas formas de distribuir os K doces existem.
    Se o N fosse fixo, era possível fazer umas contas com inclusão-exclusão do tipo: 
    
    f(n) = N^K - sum_1^N (-1)^i * comb(N, i) * (N-i)^k.

    Com essa conta, o que fazemos é incluir todas as possíveis formas de colocar doces pra todo mundo, e aí para cada i,
    fixamos os caras que não tem doces e retiramos eles. O negócio é que tirar esses caras dessa forma pode tirar
    caras a mais por causa que fixamos uma quantidade i, podendo incluir outras formas de distribuição que contém mais
    caras vazios. Por isso, quando tiramos para um índice, colocamos para o índice seguinte, para não retirar dobrado.
    A complexidade de fazer esse tipo de conta para um N fixo é O(NlogK).

    O problema todo é que se fizermos essa conta, o nosso código ficará quadrático, e aí não tem como passar no tempo.
    Quando abrimos as contas, podemos perceber que é possível agrupar algumas coisas, e podemos reduzir a equação para:

    f(n) = n! * sum{0}{n-1} (-1)^i/i! * (n-i)^i/(n-i)!

    é possível ver que temos um grupo que varia em i e outro que varia em n-i. É possível interpretar cada um desses grupos
    como se fosse um polimômio de grau n, e assim podemos realizar o processo de convolução, chamando a_i = (-1)^i/i! e
    b_i = i^k/i!. Usamos FFT para realizar isso de forma rápida, e podemos obter os resultados em O(KlogK)
    */
    _set();
    int k;
    cin >> k;

    vector<ll> a(k+1), b(k+1);
    for(int i=0; i<=k; i++) {
        a[i] = (ifat[i] * ((i%2==0) ? 1 : -1) + mod) % mod;
        b[i] = fexp(i, k)*ifat[i]%mod;
    }

    auto rs = convMod<mod>(a, b);
    for(int i=1; i<=k; i++) cout<<fat[i]*rs[i]%mod<<" ";
    cout<<"\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
