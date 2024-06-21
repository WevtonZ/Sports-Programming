// https://cses.fi/problemset/task/1740

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define mp make_pair
#define eb emplace_back
#define pb push_back
 
const int inf = 1e9;
const int N = 2e6+100;
const int off = 1e6+1;
ll bit[N];
 
void updt(int x, int val){
    while(x<N){
        bit[x]+=val;
        x+=x&-x;
    }
}
 
ll get(int x){
    ll rs=0;
    while(x){
        rs+=bit[x];
        x-=x&-x;
    }
    return rs;
}
 
ll query(int l, int r){
    return get(r)-get(l-1);
}
 
struct events{
    int y1, y2;
    bool flag;
 
    events(int a, int b, bool c) : y1(a), y2(b), flag(c) {}
};
 
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
 
    vector<vector<events>> a(N);
 
    for(int i = 0; i < n; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1+=off, x2+=off, y1+=off, y2+=off;
 
        if(y1 != y2){
            a[x1].eb(y1,y2,0);
        }
        else{
            a[x1].eb(y1,y2,0);
            a[x2].eb(y1,y2,1);
        }
    }
 
    ll rs = 0;
 
    for(int i = 1; i < N; i++){
        for(auto j: a[i]){
            if(j.y1 != j.y2){
                rs += query(j.y1, j.y2);
            }
            else{
                if(j.flag == 0) updt(j.y1, 1);
                else updt(j.y1, -1);
            }
        }
    }
 
    cout << rs << "\n";
 
    return 0;
}
