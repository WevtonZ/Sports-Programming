// https://cses.fi/problemset/task/2422

// Binary Search the Answer.

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define int long long
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
 
template<typename T, typename T1>
ostream & operator<<(ostream & os, pair<T, T1> p){
    os << "(" << p.ft << " " << p.sd << ")";
    return os;
}
 
 
template<typename T, typename T1>
istream & operator>>(istream & is, pair<T, T1>& p){
    is >> p.ft >> p.sd;
    return is;
}
 
const int N = 200100;
const int inf = 1e9;
 
 
void test(){
    int n;
    cin >> n;
 
    int l = 0, r = n*n;
 
    auto teto = [&](int a, int b){
        return (a+b-1)/b;
    };
 
    int rs = 0;
 
    while(l <= r){
        int mid = (l+r)/2;
        int cnt = 0;
        for(int i = 1; i <= n; i++){
            cnt += min(n, mid/i);
        }
 
        if(cnt >= teto(n*n, 2)){
            rs = mid;
            r = mid-1;
        }
        else 
            l = mid+1;
    }
 
    cout << rs << "\n";
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(12);
 
    int teste = 1;
    // cin >> teste;
 
    for(int k = 1; k <= teste; k++){
        test();
    }
    
    return 0;
}
