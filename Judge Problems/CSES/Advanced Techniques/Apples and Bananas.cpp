/*
  https://cses.fi/problemset/task/2111
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
 
using cd = complex<double>;
const double PI = acos(-1);
 
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
 
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
 
        if (i < j)
            swap(a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
 
    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
 
void mult(vector<ll> const& a, vector<ll> const& b, vector<ll> & res) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
 
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
 
    res.resize(n);
    for (int i = 0; i < n; i++)
        res[i] = round(fa[i].real());
 
    // multiplying polynomials.
 
    // int carry = 0;
    // for (int i = 0; i < n; i++){
    //     result[i] += carry;
    //     carry = result[i] / 10;
    //     result[i] %= 10;
    // }
}
 
void test(){
    int k, n, m;
    cin >> k >> n >> m;
 
    vector<ll> m1(k+1, 0), m2(k+1, 0);
    for(int i = 0, x; i < n; i++){
        cin >> x;
        m1[x]++;
    }
    for(int i = 0, x; i < m; i++){
        cin >> x;
        m2[x]++;
    }
 
    vector<ll> ans;
    mult(m1, m2, ans);
    for(int i = 2; i <= 2*k; i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
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
