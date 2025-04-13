// https://codeforces.com/gym/102007/attachments

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

const int N = 5005;
const ll MOD = 1e9 + 9;

ll fat[N];

ll f(ll x){
    if(x<=1) return fat[x]=1;
    if(fat[x]!=-1) return fat[x];
    return fat[x] = f(x-1)*x%MOD;
}

int a[N];

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;
    memset(fat,-1,sizeof(fat));
    set<int> S;

    for(int i = 1; i <= n; i++)
        cin >> a[i], S.insert(a[i]);

    vector<int> comp(all(S));
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(all(comp), a[i])-comp.begin()+1;
    }

    sort(a+1,a+n+1);

    vector<ll> dp(n+2,0);
    dp[0]=1;

    auto fexp = [&](ll x, ll y){
        ll rs=1;
        while(y){
            if(1&y) rs=rs*x%MOD;
            x=x*x%MOD;
            y>>=1ll;
        }
        return rs;
    };

    vector<ll> iv;
    iv.pb(1);
    for(int i = 1; i <= n; i++){
        iv.pb(fexp(i,MOD-2));
    }

    ll tmp1=1, tmp2=1;
    ll aux1=1, aux2=1;

    for(int k = 1; k <= n; k++){
        if(k==1 || a[k]!=a[k-1]) tmp1=1;
        else tmp1+=1;
        aux1=aux1*iv[tmp1]%MOD;
        dp[k]=f(k)*aux1%MOD;
        aux2=1, tmp2=1;
        for(int i = k; i>0; i--){
            dp[k]=((dp[k]-dp[i-1]*f(k-i)%MOD*aux2%MOD)+MOD)%MOD;
            if(i==k || a[i] != a[i+1]) tmp2=1;
            else tmp2+=1;
            aux2=aux2*iv[tmp2]%MOD;
        }
    }

    cout<<dp[n]<<"\n";

    return 0;
}
