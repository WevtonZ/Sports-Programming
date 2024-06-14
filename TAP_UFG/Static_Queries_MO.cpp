#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 200100;
const int K = 450;

struct query{
    int l, r, idx;

    bool operator <(const query &o){
        if(l/K == o.l/K){
            if((l/K)&1){
                return r > o.r;
            }
            return r < o.r;
        }
        return l/K < o.l/K;
    }
};

int a[N];

struct MO{
    vector<query> queries;
    vector<ll> rs;
    ll sum=0;

    MO (vector<query> queries) : queries(queries) {}

    void add(ll x){
        sum+=x;
    }

    void rmv(ll x){
        sum-=x;
    }

    // usar quando for algo mais complexo.
    // void calc(){

    // }

    void solve(){
        sort(queries.begin(), queries.end());
        rs.resize(queries.size());

        int i = 0, j = -1;
        for(auto [l, r, idx]: queries){
            while(j<r){
                j++;
                add(a[j]);
            }
            while(j>r){
                rmv(a[j]);
                j--;
            }

            while(i < l){
                rmv(a[i]);
                i++;
            }
            while(i > l){
                i--;
                add(a[i]);
            }

            rs[idx] = sum;
        }
    }
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    for(int i = 0; i < n; i++)
        cin >> a[i];

    vector<query> queries;

    for(int i = 0; i < q; i++){
        query aux;
        cin >> aux.l >> aux.r;
        aux.l--, aux.r--;
        aux.idx = i;
        queries.push_back(aux);
    }

    MO mo(queries);

    mo.solve();

    for(int i = 0; i < q; i++){
        cout << mo.rs[i] << " ";
    }
    cout << "\n";
}
