// https://cses.fi/problemset/task/1076

// It is possible to do this problem if you maintain two sets, one for numbers lower than the median and the other for numbers higher or equal to the median.

#include<bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define pb push_back

typedef long long ll;
 
const int N = 2e5+5;
const ll inf = 1e9+100;
 
int n, m;
 
vector<ll> a;
multiset<ll> low, up;
 
void inserir(ll val){
    ll v = *low.rbegin();
    if(v < val){
        up.insert(val);
        if(up.size() > m/2){
            low.insert(*up.begin());
            up.erase(up.find(*up.begin()));
        }
    }
    else{
        low.insert(val);
        if(low.size() > (m+1)/2){
            up.insert(*low.rbegin());
            low.erase(low.find(*low.rbegin()));
        }
    }
}
 
void deletar(ll val){
    if(up.find(val) != up.end())
        up.erase(up.find(val));
    else
        low.erase(low.find(val));
    
    if(low.empty()){
        low.insert(*up.begin());
        up.erase(up.find(*up.begin()));
    }
}
 
void test(){
    cin >> n >> m;
    a.resize(n);
    for(auto &i: a){
        cin >> i;
    }
    low.insert(a[0]);
    for(int i = 1; i < m; i++){
        inserir(a[i]);
    }
    cout << *low.rbegin() << " ";
    for(int i = m; i < n; i++){
        if(m == 1){
            inserir(a[i]);
            deletar(a[i-m]);
        }
        else{
            deletar(a[i-m]);
            inserir(a[i]);
        }
        cout << *low.rbegin() << " ";
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
