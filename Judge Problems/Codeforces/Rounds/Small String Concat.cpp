// https://codeforces.com/problemset/problem/632/C

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define pb push_back
#define ft first
#define sd second
#define all(x) x.begin(), x.end()

const int N = 2e5+10;

bool cmp(const string &a, const string &b){
    return (a+b) < (b+a);
}

void test(){
    vector<string> a;
    int n;
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(all(a), cmp);

    for(auto i: a)cout<<i;
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
