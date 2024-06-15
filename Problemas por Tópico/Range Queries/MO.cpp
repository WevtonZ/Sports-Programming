// codigo de MO do gustavo. Muito bom por sinal :)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back

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
    vector<int> rs;
    // posso sempre criar mais coisas se achar necessário para resolver o problema. 
    // MO é bem modificável.

    MO (vector<query> queries) {
        this->queries = queries;
    }

    void add(int x){

    }

    void rmv(int x){

    }

    int calc(){

    }

    void solve(){
        sort(all(queries));
        rs.resize(queries.size());

        int i = 1, j = 0;
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

            rs[idx] = calc();
        }
    }
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++)
        cin >> a[i];

    vector<query> queries;

    for(int i = 0; i < q; i++){
        query aux;
        cin >> aux.l >> aux.r;
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
