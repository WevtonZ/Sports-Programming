// https://codeforces.com/contest/863/problem/E

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const int N = 6e5+10;

int bit[N+1];

void updt(int x, int val){
    while(x<N){
        bit[x]+=val;
        x+=x&-x;
    }
}

int get(int x){
    int rs=0;
    while(x){
        rs+=bit[x];
        x-=x&-x;
    }
    return rs;
}

void loli(){
    int n;
    cin >> n;
    vector<tuple<int,int,int>> a(n+1);

    map<pair<int,int>, int> M;

    set<int> S;
    int ok=0;
    for(int i = 1; i <= n; i++){
        auto &[x, y, z] = a[i];
        cin >> x >> y;
        S.emplace(x);
        S.emplace(y);
        M[mp(x,y)]++;
        if(M[mp(x,y)]>1){
            ok=i;
        }
        z = i;
    }

    if(ok){
        cout<<ok<<"\n";
        return;
    }

    // duas soluções. dar merge nelas e não pensar demais.

    auto cmp = [&](tuple<int,int,int> x, tuple<int,int,int> y){
        auto [u, v, w] = x;
        auto [u2, v2, w2] = y;
        if(u == u2){
            return v > v2;
        }
        return u < u2;
    };

    sort(1+all(a), cmp);
    vector<int> comp(all(S));

    auto bb = [&](int x){
        return lower_bound(all(comp), x) - comp.begin() + 1;
    };
    vector<tuple<int,int,int>> b = a;
    for(int i = 1; i <= n; i++){
        auto &[x, y, z] = b[i];
        x = bb(x);
        y = bb(y);
    }

    vector<int> contained(n+1, 0);
    for(int i = 1; i <= n; i++){
        auto [x, y, z] = b[i];
        contained[z] += get(N) - get(y-1);
        updt(y,1);
    }

    for(int i = 1; i <= n; i++){
        if(contained[i]){
            cout<<i<<"\n";
            return;
        }
    }
    
    int l = 1;
    for(int r = 2; r <= n; r++){
        auto[l1,r1,z1] = a[l];
        auto[l2,r2,z2] = a[r];
        while(l2>r1+1){
            l++;
            tie(l1,r1,z1) = a[l];
        }
        if(r-l<=1) continue;
        auto [x, y, z] = a[l+1];
        ok=z;
        break;
    }
    if(!ok)ok--;
    cout<<ok<<"\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(12);

    int __ = 1;
    // cin >> __;

    for(int _ = 1; _ <= __; _++){
        loli();
    }
    
    return 0;
}
