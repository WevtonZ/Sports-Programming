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

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

// template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int N = 1e6+10;

vector<ll> primes;
vector<ll> aux;

void sieve() {
    vector<int> comp(N, 0);
    for(int i=2; i*i < N; i++) {
        if(!comp[i]) {
            for(int j=i*i; j<N; j+=i) comp[j]=1;
        }
    }
    for(int i=2; i<N; i++) if(!comp[i]) primes.pb(i);
}

void test() {
    ll l, r;
    cin >> l >> r;
    cout<<upper_bound(all(aux), r) - lower_bound(all(aux), l) << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    sieve();

    for(int i=0; i<primes.size(); i++) {
        ll p = primes[i];
        p = p*p+4;
        bool ok=true;
        for(auto pp: primes) {
            if(pp*pp>p) break;
            if(p%pp == 0){
                ok=false;
                break;
            }
        }
        if(ok) aux.pb(p);
    }

    int tt=1;
    cin >> tt;
    
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
        // if(_<tt) cout<<"\n";
    }
    
    return 0;
}
