// https://cses.fi/problemset/task/2112

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<double, double> pdb;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
 
const ll INF = 1e18+10;
const ll mod = 1e9+7;
const int N = 2e5+10;
 
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
 
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
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
 
    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
 
    // multiplying polynomials.
 
    // int carry = 0;
    // for (int i = 0; i < n; i++){
    //     result[i] += carry;
    //     carry = result[i] / 10;
    //     result[i] %= 10;
    // }
 
    return result;
}
 
void test(){
    vector<int> a, b;
    string s;
    cin >> s;
    int n = s.size();
 
    a.assign(n, 0);
    b.assign(n, 0);
 
    for(int i = 0; i < n; i++){
        a[i] = s[i] - '0';
        b[i] = s[n-i-1] - '0';
    }
 
    vector<int> c = multiply(a, b);
    reverse(c.begin(), c.begin()+n);
    for(int i = 1; i < n; i++){
        cout<<c[i]<<" ";
    }
    cout<<"\n";
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(12);
 
    int teste = 1;
    // cin >> teste;
 
    for(int i = 1; i <= teste; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
