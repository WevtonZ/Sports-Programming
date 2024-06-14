// https://atcoder.jp/contests/abc194/tasks/abc194_e

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const ll inf = 1e18;

// template from CP Algorithms. Idk but I think this template is dangerous.
class Mex {
private:
    map<int, int> frequency;
    set<int> missing_numbers;
    vector<int> A;

public:
    Mex(vector<int> const& A) : A(A) {
        for (int i = 0; i <= A.size(); i++)
            missing_numbers.insert(i);

        for (int x : A) {
            ++frequency[x];
            if(missing_numbers.find(x) != missing_numbers.end())
                missing_numbers.erase(x);
        }
    }

    int mex() {
        return *missing_numbers.begin();
    }

    void update(int idx, int new_value) {
        if (--frequency[A[idx]] == 0)
            missing_numbers.insert(A[idx]);
        A[idx] = new_value;
        ++frequency[new_value];
        missing_numbers.erase(new_value);
    }
};

void loli(){
    int n, m;
    cin >> n >> m;

    vector<int> a(n,1e9);
    Mex M(a);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int rs = 1e8;
    for(int i = 0; i < m; i++){
        M.update(i, a[i]);
    }
    rs = min(rs,M.mex());
    for(int i = m; i < n; i++){
        M.update(i-m, 1e9);
        M.update(i, a[i]);
        rs = min(rs,M.mex());
    }
    cout<<rs<<"\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(12);

    int __ = 1;
    // cin >> __;

    for(int _ = 1; _ <= __; _++){
        loli();
    }
    
    return 0;
}
