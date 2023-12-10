// Palindrome Queries - CSES Solution
// link: https://cses.fi/problemset/task/2420

/*
    The idea is that you can maintain two hash tables, one for the original string and the other
    for it's reverse form, and do point updates in both of them in O(logn) time. This can be done 
    with a BIT or a Segment Tree. This one uses a BIT to do updates and queries.
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define debug cout
#define ft first
#define sd second
#define pb push_back
 
const int N = 2e5+3;
 
struct updtHash{
    ll p, mod, ppow[N], ppow2[N], mod2, p2;
    pair<ll,ll> h[N];
 
    updtHash() : p(33), mod(1000000007), p2(73), mod2(1000000009) {
        ppow[0] = 1;
        ppow2[0] = 1;
        for (int i = 1; i < N; i++) {
            ppow[i] = (ppow[i-1] * p) % mod;
            ppow2[i] = (ppow2[i-1] * p2) % mod2;
        }
    }
 
    ll inv(ll x, int w){
        ll md = (w ? mod2 : mod);
        ll b = md-2;
        ll rs = 1;
 
        while(b){
            if(1&b) rs = rs*x%md;
            x = x*x%md;
            b >>= 1;
        }
        return rs;
    }

    void updt(int x, pair<ll,ll> v){
        while(x < N){
            h[x].ft += v.ft;
            h[x].sd += v.sd;
            if(h[x].ft > mod) h[x].ft -= mod;
            if(h[x].sd > mod2) h[x].sd -= mod2;
            x += (x&-x);
        }
    }
 
    pair<ll,ll> get(int x){
        pair<ll,ll> r = {0ll, 0ll};
        while(x){
            r.ft += h[x].ft;
            r.sd += h[x].sd;
            if(r.ft > mod) r.ft -= mod;
            if(r.sd > mod2) r.sd -= mod2;
            x -= (x&-x);
        }
 
        return r;
    }

    void init(string &s) {
        for (int i = 0; i < s.size(); i++) {
            int code = s[i];
            pair<ll, ll> v;
            v.first = code * ppow[i+1] % mod;
            v.second = code * ppow2[i+1] % mod2;
            updt(i+1, v);
        }
    }
 
    pair<ll,ll> get_hash(int i, int j){
        pair<ll,ll> r, l;
        r = get(j+1);
        l = get(i);
        r.ft = (r.ft - l.ft + mod) * inv(ppow[i], 0) % mod;
        r.sd = (r.sd - l.sd + mod2) * inv(ppow2[i], 1) % mod2;
 
        return r;
    }
 
    void updt_char(int i, int code){
        pair<ll,ll> l, r, v;
        r = get(i+1);
        l = get(i);
        v.ft = (code * ppow[i+1] - r.ft + l.ft + mod) % mod;
        v.sd = (code * ppow2[i+1] - r.sd + l.sd + mod2) % mod2;
        updt(i+1, v);
    }
};
 
updtHash h1, h2;
 
void test(){
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
 
    h1.init(s);
    reverse(all(s));
    h2.init(s);
 
    while(q--){
        int t;
        cin >> t;
        if(t == 1){ // do updates. Call updt_char always. Do not use the updt function.
            int x;
            char c;
            cin >> x >> c;
            h1.updt_char(x-1, c);
            h2.updt_char(n-x, c);
        }
        else{ // find if they are equal.
            int l, r;
            cin >> l >> r;
            pair<ll,ll> v1, v2;
            v1 = h1.get_hash(l-1, r-1);
            v2 = h2.get_hash(n-r, n-l);
            if(v1 == v2){
                cout<<"YES\n";
            }
            else{
                cout<<"NO\n";
            }
        }
    }
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
    // cin >> teste;
 
    while(teste--){
        test();
    }
 
    return 0;
}
