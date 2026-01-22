#include <bits/stdc++.h>
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1ll << (i)) & (x)) // testar bit i no valor x
#define mp make_pair
#define mt make_tuple
#define dbg(x) cout << #x << " = " << x << endl;
#define el '\n'

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

// template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const ll mod = 998244353;
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

const int N = 2e5+10;
mi bit[N];

void updt(int x, mi v) {
    while(x<N){
        bit[x]+=v;
        x+=x&-x;
    }
}

mi get(int x) {
    mi rs=0;
    while(x){
        rs+=bit[x];
        x-=x&-x;
    }
    return rs;
}

void test() {
    /*
    Calcular sum_{i=l}^{r}(a_i * prod_{j=l}^{r-1}(b_j)). Ideia é calcular o sufixo de b_j, colocar todo a_i*suf_i na bit/seg e depois pegar o resultado de
    (get(r)-get(l-1))/suf[r].
    */
    int n;
    cin >> n;
    
    vector<int> a(n+1), b(n);
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=1; i<n; i++) cin >> b[i];

    vector<mi> suf(n,1);
    suf.pb(1);
    for(int i=n-1; i>0; i--) suf[i]=suf[i+1]*b[i];
    for(int i=1; i<=n; i++) updt(i,a[i]*suf[i]);
    
    int q; cin >> q;

    while(q--){
        int l,r; cin >> l >> r;
        cout<<(get(r)-get(l-1))/suf[r]<<el;
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
        // if(_<tt) cout<<"\n";
    }
    
    return 0;
}
