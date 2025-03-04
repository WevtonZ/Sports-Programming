// https://atcoder.jp/contests/abc392/tasks/abc392_f

#include <bits/stdc++.h>
using namespace std;

#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

using ll = long long;
using ld = long double;
using i128 = __int128_t;

// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T, typename T1> ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1> istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

#define tipo int
struct Node{
    int p,cnt;
    int value;
    bool rev;  
    struct Node * l;
    struct Node * r;
    Node() { }
    Node(tipo value) : value(value), p(rng()),cnt(1),rev(false), l(nullptr), r(nullptr) {}

};
typedef Node * pnode;

int cnt (pnode t) {
    return t ? t->cnt : 0;
}

void upd_cnt (pnode t) {
    if (t){
        
        t->cnt = 1 + cnt(t->l) + cnt (t->r);
    } 
}

void push (pnode it) {
    if (it && it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
        //upd_cnt(it);
    }
}

void split(pnode t, pnode &l, pnode &r,int key,int add = 0){
    if(!t){
        return void( l = r = nullptr );
    }
    push(t);
    int cur_key=add+cnt(t->l);
    if(key<=cur_key){
        split(t->l,l,t->l,key,add);
        r=t;
    }else{
        split(t->r,t->r,r,key,add+1+cnt(t->l));
        l=t;
    }
    upd_cnt(t);
}

void merge(pnode &t,pnode l, pnode r){
    push(l);
    push(r);
    if (!l || !r)
        t = l ? l : r;
    else if(l->p>r->p){
        merge(l->r,l->r,r),t=l;
    }else{
        merge(r->l,l,r->l),t=r;
    }
    upd_cnt (t);
}

void insert(pnode &t,pnode n,int key){  
    pnode t1,t2;
    split(t,t1,t2,key);
    merge(t1,t1,n);
    merge(t,t1,t2);
}

void reverse (pnode t, int l, int r) {
    if(l>=r)
        return;
    pnode t1,t2,t3;
    split (t, t1, t2, l);
    split (t2, t2, t3, r-l+1);
    t2->rev ^= true;
    merge (t, t1, t2);
    merge (t, t, t3);
}
void output (pnode t) {
    if (!t)  return;
    output (t->l);
    cout<<t->value<<" ";
    output (t->r);
}
void clr (pnode &t) {
    if (!t)  return;
    clr (t->l);
    clr (t->r);
    delete t;
    t=NULL;
    // cout<<t<<"\n";
}

void erase(pnode &t,int key)
{
    pnode t1,t2,t3;
    split(t,t1,t2,key-1);
    split(t2,t2,t3,key);
    merge(t,t1,t3);
}

void test(){
    int n;
    cin >> n;
    pnode t = NULL;
    for(int i=1; i<=n; i++){
        int x;
        cin >> x;
        insert(t, new Node(i), x-1);
    }
    output(t);
    clr(t);
    cout<<"\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(15);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
