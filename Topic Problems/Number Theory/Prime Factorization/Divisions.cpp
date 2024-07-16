// https://codeforces.com/gym/100753/attachments

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

using u64 = uint64_t;
using u128 = __uint128_t;

istream &operator>>(istream &is,u128 &v) {
    string s;
    is>>s;
    v=0;
    for(auto &it:s) if(isdigit(it)) v=v*10+it-'0';
    if(s[0]=='-') v*=-1;
    return is;
}

ostream &operator<<(ostream &os,const u128 &v) {
    if(v==0) return (os<<"0");
    u128 num=v;
    if(v<0) os<<'-',num=-num;
    string s;
    for(;num>0;num/=10) s.pb((char)(num%10)+'0');
    reverse(all(s));
    return (os<<s);
}

const u128 N = 2e6+10;

bitset<N> primes;
vector<int> spf;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void sieve(){
    primes.set();
    primes[0]=primes[1]=false;
    spf.resize(N);
    for(int i = 1; i < N; i++) spf[i]=i;

    for(ll i = 2; i*i < N; i++){
        if(primes[i]){
            for(ll j = i+i; j < N; j += i){
                primes[j]=false;
                spf[j]=min<int>(spf[j],i);
            }
        }
    }
}

u128 binpower(u128 base, u128 e, u128 mod) {
    u128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u128 n, u128 a, u128 d, int s) {
    u128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=15) {
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rng() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

u64 fexp(u64 a, u64 b, u64 mod){
    u64 rs=0;
    while(b){
        if(b&1ll) rs=(rs+a)%mod;
        a = (a+a)%mod;
        b>>=1ll;
    }
    return rs;
}

u64 f(u64 x, u64 c, u64 mod) {
    return ((u128) x * x + c) % mod;
}

u64 gcd(u64 a, u64 b){
    // cout<<a<<" "<<b<<"\n";
    if(b==0) return a;
    return gcd(b,a%b);
}

u64 abs(u64 a, u64 b){
    return a>=b ? a-b : b-a;
}

u64 rho(u64 n, u64 x0=2, u64 c=1){
    u64 x = x0;
    u64 y = x0;
    u64 g=1;
    while(g==1){
        // cout<<g<<"\n";
        x = f(x,c,n);
        y = f(y,c,n);
        y = f(y,c,n);
        g = gcd(abs(x,y),n);
    }
    return g;
}

vector<u64> fact(u64 n){
    // casos base: cara ser 1 ou cara ser primo.
    // usa-se Miller Rabin pra testar primalidade.

    if(n == 1) return vector<u64>();
    if(MillerRabin(n)) return vector<u64> {n};

    // seguir em frente:
    vector<u64> u, v;
    while(n>1 && n<N){
        u.pb(spf[n]);
        n/=spf[n];
    }

    if(n>=N){
        u64 x = rho(n);

        u = fact(x);
        v = fact(n/x);

        for(auto i:v) u.pb(i);
    }
    return u;
}

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);

    sieve();

    ll x;
    cin >> x;
    vector<u64> f = fact(x);
    map<u64,int> M;
    for(int i = 0; i < f.size(); i++) M[f[i]]++;

    u64 rs=1;
    for(auto [_, ct]: M){
        rs *= (u64)(ct+1);
    }

    cout<<rs<<"\n";

    return 0;
}
