// https://cses.fi/problemset/task/1730/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define pb push_back
 
void test(){
    int n;
    int x = 0;
    cin >> n;
 
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        x ^= a;
    }
    if(x) cout << "first\n";
    else cout << "second\n";
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
