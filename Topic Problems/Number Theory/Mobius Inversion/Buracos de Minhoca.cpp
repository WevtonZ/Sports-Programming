// https://codeforces.com/group/btcK4I5D5f/contest/308631/problem/B

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
#define eb emplace_back
#define pb push_back
 
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
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#pragma endregion

const int N = 4e5+10;

vector<int> p; // vetor de primos
bitset<N> b; // vetor para marcar os primos.
int mu[N]; // funcao de mobius.
int lp[N]; // guardar o menor primo que divide meu atual.

// func pra verificar o valor de mu[x].
int verif(int x) {
    int ct = 0;
    while(x>1){
        int d = lp[x], k=0;
        while(x%d==0){
            x /= d;
            k++;
            if(k>1) return 0;
        }
        ct++;
    }
    if(ct%2) return -1;
    return 1;
}

void sieve() {
    mu[1] = 1;
    b.set();
    b[0] = b[1] = false;
    for(int i=2; i<N; i++) {
        if(b[i]){
            for(int j=i; j<N; j+=i){
                if(!lp[j]) lp[j] = i;
            }

            mu[i] = verif(i);
        }
    }
}

void test(){
    sieve();
    int n;
    cin >> n;

    vector<ll> rs(n+1, 0);
    for(int i=1; i<=n; i++) {
        for(int d=1; d<=n/i; d++) {
            ll v = (n/i)/d;
            rs[i] += mu[d]*v*v;
        }
    }

    for(int i=1; i<=n; i++) cout<<rs[i]<<" ";
    cout<<"\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(15);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
