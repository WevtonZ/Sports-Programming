// https://codeforces.com/contest/632/problem/E

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define pb push_back
#define ft first
#define sd second

typedef long long ll;

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
    for (int i = 0; i < n; i++){
        result[i] = round(fa[i].real());
        result[i] = min(result[i], 1);
    }
    return result;
}

vector<int> a;

void test(){
    int n, k;
    cin >> n >> k;
    a.resize(1001, 0);
    for(int i = 0, x; i < n; i++) cin >> x, a[x]++;
    vector<int> ans(1, 1);
    while(k){
        if((1&k)) ans = multiply(ans, a);
        a = multiply(a, a);
        k >>= 1;
    }
    for(int i = 0; i < ans.size(); i++){
        if(ans[i]) cout<<i<<" ";
    }
    cout<<"\n";
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    // cout << fixed << setprecision(12);

    int teste = 1;
    // cin >> teste;

    while(teste--){
        test();
    }

    return 0;
}
