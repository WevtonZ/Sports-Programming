// https://cses.fi/problemset/task/1098/

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
 
const int N = 2e5+10;
 
vector<int> a;
 
void test(){
    int n, k = 4;
    cin >> n;
 
    a.resize(n);
 
    for(auto &i: a) cin >> i;
    for(int i = 0; i < n; i++){
        a[i] %= k;
    }
    int nsum = 0;
    for(int i = 0; i < n; i++){
        nsum ^= a[i];
    }
    if(nsum == 0) cout<<"second\n";
    else cout<<"first\n";
}
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
    cin >> teste;
 
    while(teste--){
        test();
    }
    
    return 0;
}
