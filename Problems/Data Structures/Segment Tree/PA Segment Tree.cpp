// https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/B

#include "bits/stdc++.h"
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1 << i) & x)
#define mp make_pair
#define mt make_tuple

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int N = 2e5+10;

ll tree[N << 2];
// [primeiro termo, razao]
pair<ll,ll> lazy[N << 2];
const int emp = 0;
const pair<ll,ll> emp2 = {0,0};

// conta = a_1 + (n-1)*r, com r a razão e a_1 o termo inicial da PA.
ll sumAP(ll A, ll D, ll len){
    return len * A + D * ((len * (len - 1)) / 2);
}

ll f(ll l, ll r) {
    return l+r;
}

void push(int x, int tl, int tr) {
    if(tl == tr || lazy[x] == emp2) return;
    int tm = (tl + tr) >> 1;
    ll vl = tm-tl+1;
    ll vr=tr-tm;

    ll al = lazy[x].ft;
    ll dl = lazy[x].sd;
    ll ar = lazy[x].ft+lazy[x].sd*vl;
    ll dr = lazy[x].sd;

    lazy[lef(x)].ft += al;
    lazy[lef(x)].sd += dl;
    
    lazy[rig(x)].ft += ar;
    lazy[rig(x)].sd += dr;
    
    tree[lef(x)] += sumAP(al, dl, vl);
    tree[rig(x)] += sumAP(ar, dr, vr);
    
    lazy[x] = emp2;
}

void updt(int x, int tl, int tr, int l, int r, ll a, ll d) {
    if(tl > r || tr < l) return;
    else if(tl >= l && tr <= r) {
        ll v = (tr-tl+1);
        tree[x] += sumAP(a+(tl-l)*d, d, v);
        lazy[x].ft += a+(tl-l)*d;
        lazy[x].sd += d;
    }
    else{
        push(x, tl, tr);
        int tm = (tl + tr) >> 1;
        updt(lef(x), tl, tm, l, r, a, d);
        updt(rig(x), tm+1, tr, l, r, a, d);

        tree[x] = f(tree[lef(x)], tree[rig(x)]);
    }
}

ll query(int x, int tl, int tr,int pos) {
    if(tl == tr) return tree[x];
    else{
        push(x, tl, tr);
        int tm = (tl + tr) >> 1;
        if(pos <= tm) return query(lef(x), tl, tm, pos);
        else return query(rig(x), tm+1, tr, pos);
    }
}

void test() {
    int n, q;
    cin >> n >> q;

    while(q--){
        int t; cin >> t;
        if(t == 1) {
            int l, r, a, d;
            cin >> l >> r >> a >> d;
            updt(1,1,n,l,r,a,d);
        }
        else {
            int p; cin >> p;
            cout << query(1,1,n,p) << "\n";
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);
    
    int tt=1;
    // cin >> tt;
    
    while(tt--){
        test();
    }
    
    return 0;
}
