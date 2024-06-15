// https://cses.fi/problemset/task/1077

// there was some math towards this problem, although I forgot after a day or so. It was not that hard though.

#include<bits/stdc++.h>
using namespace std;
 
#pragma region
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2", "popcnt")
 
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define pb push_back
 
typedef long double ld;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;
 
template<class T> using ordset = tree<T,
                        null_type, less<T>, 
                        rb_tree_tag, tree_order_statistics_node_update>;
 
#pragma endregion
 
const int N = 2e5+5;
const ll inf = 1e9+100;
 
ll n, k;
 
vector<ll> a;
multiset<ll> low, up;
ll S1, S2;
 
void inserir(ll val){
    ll prev = *low.rbegin();
    if(prev < val){
        up.insert(val);
        S1 += val;
        if(up.size() > k/2){
            low.insert(*up.begin());
            S2 += *up.begin();
            S1 -= *up.begin();
            up.erase(up.find(*up.begin()));
        }
    }
    else{
        low.insert(val);
        S2 += val;
        if(low.size() > (k+1)/2){
            up.insert(*low.rbegin());
            S1 += *low.rbegin();
            S2 -= *low.rbegin();
            low.erase(low.find(*low.rbegin()));
        }
    }
}
 
void deletar(ll val){
    if(up.find(val) != up.end()){
        S1 -= val;
        up.erase(up.find(val));
    }
    else{
        S2 -= val;
        low.erase(low.find(val));
    }
 
    if(low.empty()){
        S2 += *up.begin();
        low.insert(*up.begin());
        S1 -= *up.begin();
        up.erase(up.find(*up.begin()));
    }
}
 
void test(){
    cin >> n >> k;
 
    a.resize(n);
    for(auto &i: a){
        cin >> i;
    }
    
    low.insert(a[0]);
    S2 += a[0];
    
    for(int i = 1; i < k; i++){
        inserir(a[i]);
    }
    cout << S1 - S2 + (1&k ? *low.rbegin() : 0) << " ";
    for(int i = k; i < n; i++){
        if(k == 1){
            inserir(a[i]);
            deletar(a[i-k]);
        }
        else{
            deletar(a[i-k]);
            inserir(a[i]);
        }
 
        ll median = *low.rbegin();
        cout << S1 - S2 + (1&k ? median : 0)<< " ";
    }
    cout << "\n";
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;  
    // cin >> teste;
 
    while(teste--){
        test();
    }
    
    return 0;
}
