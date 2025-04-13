// https://cses.fi/problemset/task/1655

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
 
// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T, typename T1>
ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1>
istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}

#pragma endregion

const int K = 30;

class Trie {
    public:

    map<int,Trie> M;

    void add(int x, int at = K) {
        if(at >= 0) {
            int s = !!((1 << at) & x);
            M[s].add(x, at-1);
        }
    }

    int find(int x, int at = K) {
        int rs=0;
        if(at >= 0) {
            int s = !!((1 << at) & x);
            if(M.count(s^1)) rs += (1 << at) + M[s^1].find(x, at-1);
            else rs += M[s].find(x, at-1);
        }
        return rs;
    }
};

void test() {
    /*
        Pra achar o XOR máximo de um subarray, podemos só jogar tudo em uma trie e fazer um guloso nela. Vemos se podemos
        achar um cara na trie que dá o melhor matching com o nosso cara atual, e depois disso podemos só adicionar os prefixos
        de XOR nela, pra depois consultar.
    */

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    Trie trie;
    trie.add(0);
    int xx = 0;
    int rs=0;
    for(int i=0; i<n; i++) {
        xx^=a[i];
        rs = max(rs, trie.find(xx));
        trie.add(xx);
    }
    cout << rs << "\n";
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
