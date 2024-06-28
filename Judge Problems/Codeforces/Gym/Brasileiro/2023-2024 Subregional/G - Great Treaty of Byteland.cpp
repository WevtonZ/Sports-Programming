// https://codeforces.com/gym/104555/problem/G

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

const int N = 1e5+5;
const ll inf = 1e16;

typedef pair<int,int> pt;

int orientation(pt a, pt b, pt c) {
    int v = a.ft*(b.sd-c.sd)+b.ft*(c.sd-a.sd)+c.ft*(a.sd-b.sd);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o > 0 || (include_collinear && o == 0);
}

void convex_hull(vector<pt>& a, bool include_collinear = false){
    if (a.size() == 1)
        return;
    
    set<pair<pt,int>> S;
    for(int i = 0; i < a.size(); i++){
        S.insert({a[i],i});
    }

    sort(a.begin(), a.end());
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2, include_collinear)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i], include_collinear))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2, include_collinear)) {
            while (down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i], include_collinear))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    if (include_collinear && up.size() == a.size()) {
        reverse(a.begin(), a.end());
        for(int i = 1; i <= a.size(); i++){
            cout<<i<<" ";
        }
        cout<<"\n";
        return;
    }
    a.clear();

    set<int> rs;

    for (int i = 0; i < (int)up.size(); i++){
        a.push_back(up[i]);
        auto f = S.lower_bound(mp(a.back(),0));
        rs.insert(f->sd+1);
        S.erase(f);
    }

    for (int i = down.size() - 2; i > 0; i--){
        a.push_back(down[i]);
        auto f=S.lower_bound(mp(a.back(),0));
        rs.insert(f->sd+1);
        S.erase(f);
    }

    for(auto i: rs){
        cout<<i<<" ";
    }
    cout<<"\n";
}

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<pt> a;

    int n; cin >> n;
    for(int i = 0; i < n; i++){
        pt x;
        cin >> x.ft >> x.sd;
        a.pb(x);
    }

    convex_hull(a,1);

    return 0;
}
