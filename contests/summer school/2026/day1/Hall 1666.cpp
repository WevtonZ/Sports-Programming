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

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

// template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

bool ask(string x) {
    cout << "? " << x << endl;
    bool y; cin >> y;
    return y;
}

void say(string x) {
    cout << "! " << x << endl;
}

void test() {
    /*
    Problem where you want to find how 1666 is written in roman numerals but the numerals were written in lowercase letters from a to g.
    The thing is, you can use some facts from the roman numerals (such as 2 fives cannot be put together) to guess some of the numbers, and then the rest is quite easy to find afterwards.
    */
  
    vector<char> unit, fives;
    for(char c = 'a'; c <= 'g'; c++) {
        string x;
        x.pb(c);
        x.pb(c);
        if(ask(x) == 1) {
            unit.pb(c);
        }
        else{
            fives.pb(c);
        }
    }
    
    auto t1 = [&](char c, char d) {
        string tmp;
        tmp.pb(c); tmp.pb(d);
        if(ask(tmp)) return true;
        return false;        
    };

    if(t1(fives[0],fives[1])) swap(fives[0],fives[1]);
    if(t1(fives[0],fives[2])) swap(fives[0],fives[2]);
    if(t1(fives[1],fives[2])) swap(fives[1],fives[2]);

    auto t2 = [&](char c, char d, char e) {
        string tmp;
        tmp.pb(c); tmp.pb(d); tmp.pb(e);
        if(ask(tmp)) return true;
        return false;
    };

    for(int i=0; i<unit.size(); i++) {
        for(int j=i+1; j<unit.size(); j++) {
            if(t2(unit[i], unit[j], unit[j])) swap(unit[i], unit[j]);
        }
    }
    string rs;
    while(unit.size() && fives.size()) {
        rs.pb(unit.back());
        rs.pb(fives.back());
        unit.pop_back();
        fives.pop_back();
    }
    rs.pb(unit.back());
    say(rs);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    int tt=1;
    cin >> tt;
    
    for(int _=1; _<=tt; _++) {
        // cout<<"Case #"<<_<<": ";
        test();
        // if(_<tt) cout<<"\n";
    }
    
    return 0;
}
