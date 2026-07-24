#include <bits/stdc++.h>
using namespace std;
 
#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(i, x) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'
 
using ll = long long;
using ld = long double;
 
template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const ll mod = 1e9+7;
struct mi {
    int v;
    explicit operator int() const { return v; }
    mi(ll vv = 0) : v(vv % mod) { v += (v < 0) * mod; }
    friend mi& operator+=(mi& a,mi b){if((a.v += b.v) >= mod) a.v -= mod; return a;}
    friend mi& operator-=(mi& a,mi b){if((a.v -= b.v) < 0) a.v += mod; return a;}
    friend mi& operator*=(mi& a,mi b){a.v = 1ll*a.v*b.v%mod; return a;}
    friend mi& operator/=(mi& a,mi b){a *= inv(b); return a;}
    friend mi operator+(mi a,mi b){return a += b;}
    friend mi operator-(mi a,mi b){return a -= b;}
    friend mi operator*(mi a,mi b){return a *= b;}
    friend mi operator/(mi a,mi b){return a /= b;}
    friend mi fexp(mi a, ll b){
        mi ans = 1;
        while(b){
            if(b&1) ans *= a;
            b >>= 1;
            a *= a;
        }
        return ans;
    }
    friend mi inv(mi a){return fexp(a,mod-2);}
    friend ostream& operator<<(ostream& out, mi at){return out << at.v;}
    friend istream& operator>>(istream& in, mi &at){return in>>at.v;}
};
 
const int N = 11, M = 1010;
 
mi dp[M][1 << N];
 
void test() {
    /**
     * Esse problema pede para contar de quantas formas voce consegue colocar peças de tamanho
     * 1x2 e 2x1 em uma grid N*M. Para esse problema, N <= 10, então podemos abusar desse fato para
     * fazer alguma coisa.
     * 
     * A ideia principal para resolver esse problema é usar esse estado como uma máscara que me diz
     * se o espaço i está ocupado pela peça anterior (isto é, eu escolhi deixar uma peça deitada
     * na coluna anterior que vazou para a atual). Assim, temos alguns tipos de estados que são válidos:
     * 
     * 0 0 -> posso fazer qualquer coisa
     * 1 0 -> posso só colocar vazando
     * 1 1 -> posso só aceitar que vazou
     * 
     * Entao a ideia aqui é fazer uma DP em cima dessas coisas, onde eu só preciso saber se, a partir
     * do estado que eu to, eu consigo alcançar um próximo e qual é ele. Podemos guardar as coisas
     * como se fossem uma adjacência num grafo, precalculando os próximos estados, e a partir disso
     * ir contando a resposta na dp.
     */
    int n, m;
    cin >> n >> m;
 
    auto check = [&](int m1, int m2) -> bool {
        int i=0;
        while(i<n){
            bool at = (m1&(1<<i))>0, prox=(m2&(1<<i))>0;
            if(at){ // coluna anterior ocupa esse cara
                if(prox) return false;
                i++;
            }
            else{
                if(prox) i++;
                else{
                    if(i+1>=n) return false;
                    int att = (m1&(1<<(i+1)))>0;
                    int proxx = (m2&(1<<(i+1)))>0;
                    if(att || proxx) return false;
                    i+=2; // encaixei uma peça vertical (ou horizontal. eu nao sei direção)
                }
            }
        }
        return true;
    };
 
    vector<vector<int>> comp(1<<N);
    for(int i=0; i<(1<<n); i++){
        for(int j=0; j<(1<<n); j++){
            if(check(i,j)) comp[i].push_back(j);
        }
    }
 
    dp[0][0]=1;
    for(int i=1; i<=m; i++){
        for(int mask=0; mask<(1<<n);mask++){
            for(auto prox: comp[mask]) dp[i][prox]+=dp[i-1][mask];
        }
    }
 
    cout<<dp[m][0]<<el;
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
