#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

const int N = 200010;
const int K = 450;

struct query{
    int l, r, k, idx;

    bool operator <(const query &o){
        if(l/K == o.l/K){
            if((l/K)&1)
                return r > o.r;
            return r < o.r;
        }
        return l/K < o.l/K;
    }
};

int a[N];
int cnt[N], cnt2[N];
int n, q;

struct MO{
    vector<query> queries;
    vector<int> rs;
    ll mx=0;

    MO(vector<query> queries){
        this->queries = queries;
    }

    void add(int x){
        cnt2[cnt[x]]--;
        cnt[x]++;
        cnt2[cnt[x]]++;
        if(cnt[x]>mx) mx++;
    }

    void rmv(int x){
        cnt2[cnt[x]]--;
        if(cnt2[cnt[x]]==0 && cnt[x]==mx)
            mx--;
        cnt[x]--;
        cnt2[cnt[x]]++;
    }

    int calc(ll k, ll l, ll r){
        return k*mx >= (r-l+1);
    }

    void solve(){
        sort(all(queries));
        rs.resize(queries.size());

        int i = 1, j = 0;
        for(auto [l, r, k, idx]: queries){
            while(j < r){
                j++;
                add(a[j]);
            }

            while(j > r){
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

            rs[idx] = calc(k, l, r);
        }
    }
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    cnt2[0]=n;
    vector<int> rdx;
    for(int i = 1; i <= n; i++) cin >> a[i], rdx.pb(a[i]);

    sort(all(rdx));
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(all(rdx), a[i]) - rdx.begin() + 1;
    }

    vector<query> queries;
    for(int i = 0; i < q; i++){
        query aux;
        cin >> aux.l >> aux.r >> aux.k;
        aux.idx = i;
        queries.pb(aux);
    }

    MO mo(queries);
    mo.solve();

    for(int i = 0; i < q; i++)
        cout<<(mo.rs[i]?"YES":"NO")<<"\n";

    return 0;
}
