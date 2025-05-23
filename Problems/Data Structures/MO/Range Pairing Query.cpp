// https://atcoder.jp/contests/abc242/tasks/abc242_g

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back

const int N = 1e5+5;
const int K = 315;

int a[N], cnt[N];

struct query{
    int l, r, idx;

    bool operator <(const query &o){
        if(l/K == o.l/K){
            if((l/K)&1){
                return r > o.r;
            }
            return r<o.r;
        }
        return l/K<o.l/K;
    }
};

struct MO{
    vector<query> queries;
    vector<int> rs;
    int sum=0;

    MO(vector<query> queries){
        this->queries = queries;
    }

    void add(int x){
        int v=cnt[x]++;
        sum-=v/2;
        v=cnt[x];
        sum+=v/2;
    }

    void rmv(int x){
        int v=cnt[x]--;
        sum-=v/2;
        v=cnt[x];
        sum+=v/2;
    }

    int calc(){
        return sum;
    }

    void solve(){
        sort(all(queries));
        rs.resize(queries.size());

        int i = 1, j = 0;
        for(auto [l, r, idx]: queries){
            while(j < r){
                j++;
                add(a[j]);
            }

            while(j > r){
                rmv(a[j]);
                j--;
            }

            while(i > l){
                i--;
                add(a[i]);
            }

            while(i < l){
                rmv(a[i]);
                i++;
            }

            rs[idx]=calc();
        }
    }
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, q;
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    cin >> q;

    vector<query> queries;
    for(int i = 0; i < q; i++){
        query aux;
        cin >> aux.l >> aux.r;
        aux.idx=i;
        queries.pb(aux);
    }

    MO mo(queries);
    mo.solve();
    for(int i = 0; i < q; i++){
        cout<<mo.rs[i]<<" ";
    }
    cout<<"\n";

    return 0;
}
