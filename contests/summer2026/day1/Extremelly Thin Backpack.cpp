#include <bits/stdc++.h>
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1ll << (i)) & (x)) // testar bit i no valor x
#define mp make_pair
#define mt make_tuple
#define dbg(x) cout << #x << " = " << x << endl;
#define el '\n'

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

// template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

void test() {
    int n;
    ll V;
    cin >> n >> V;
    vector<ll> c(n+1), v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i];
    for(int i=1; i<=n; i++) cin >> c[i];
    ll rs=0;
    if(V <= 400) {
        // dbg("entrei");
        vector<ll> dp(V+1, 0);
        dp[0]=0;
        for(int i=1; i<=n; i++) {
            for(int j=V; j >= v[i]; j--) {
                dp[j] = max(dp[j],dp[j-v[i]] + c[i]);    
            }
        }
        for(int i=0; i<=V; i++) {
            rs=max(rs,dp[i]);
        }
    }
    else{
        ll tmp=0;
        for(int i=1; i<=n; i++) { // primeira resposta: pegar um cara só.
            tmp=max(tmp,c[i]);
        }

        vector<pair<ll,ll>> x;
        for(int i=1; i<=n; i++) x.pb(mp(v[i],c[i]));
        sort(all(x));

        vector<pair<pair<ll,ll>,pair<ll,ll>>> mx;
        mx.pb(mp(mp(x[0].sd,0),mp(-1,-1)));
        for(int i=1; i<n; i++) {
            if(x[i].sd>mx.back().ft.ft){
                mx.pb(mp(mp(x[i].sd,i),mx[i-1].ft));
            }
            else if(x[i].sd > mx.back().sd.ft){
                mx.pb(mp(mx.back().ft, mp(x[i].sd,i)));
            }
            else{
                mx.pb(mx.back());
            }
        }

        // for(auto [u, v]: mx) {
        //     cout<<u.ft<<" "<<u.sd<<" "<<v.ft<<" "<<v.sd<<"\n";
        // }

        for(int i=0; i<n; i++) {
            int l=i+1, r=n-1;
            int id=-1;
            while(l<=r){
                int mid=l+r;
                mid>>=1;
                if(x[mid].ft+x[i].ft<=V){
                    id=mid;
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            if(id!=-1){
                if(mx[id].ft.sd != i){
                    tmp=max(tmp,mx[id].ft.ft+x[i].sd);
                }
                else if(mx[id].sd.sd != i){
                    tmp=max(tmp,mx[id].sd.ft+x[i].sd);
                }
            }
        }

        // resposta com 3 caras, no máximo.

        ll tr = (3ll*V)/(V-100);
        for(int qt=3; qt<=tr; qt++) {
            int d=(V-100)/3;
            int r=V-qt*d;

            for(int i=1; i<=n; i++){
                v[i]-=d;
                // cout<<v[i]<<" ";
            }
            // cout<<el;
            // cout<<r<<el;

            vector<vector<ll>> dp(qt+1, vector<ll>(r+1, 0));
            for(int i=1;i<=n; i++) for(int j=qt; j>0; j--) for(int k=r; k>=v[i]; k--) {
                dp[j][k] = max(dp[j][k], dp[j-1][k-v[i]]+c[i]);
            }

            for(int i=1; i<=n; i++) v[i]+=d;
            for(int i=1; i<=r; i++) tmp=max(tmp, dp[qt][i]);
        }

        rs=max(rs,tmp);
    }

    cout<<rs<<"\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    int tt=1;
    cin >> tt;
    
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
        // if(_<tt) cout<<"\n";
    }
    
    return 0;
}
