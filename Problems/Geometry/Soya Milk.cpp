#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define get_bit(i, x) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

using ll = long long;
using ld = long double;

template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ld EPS = 1e-8;

template<typename T> int sgn(T x) { return (x > EPS) - (x < -EPS); }
const ld pi = acosl(-1.0l);

ld rad(ld x) {
    return x*pi/180;
}

ld deg(ld x) {
    return x*180/pi;
}

template<class T> struct Point {
    T x,y;
    Point(T _x=0, T _y=0) : x(_x), y(_y) {}

    friend istream &operator>>(istream &is, Point & o){
        is >> o.x >> o.y;
        return is;
    }

    Point operator+(const Point & o) const { return Point(x+o.x, y+o.y); }
    Point operator-(const Point & o) const { return Point(x-o.x, y-o.y); }

    bool operator==(const Point &o) const { return sgn(x-o.x) == 0 && sgn(y-o.y) == 0; }
    bool operator<(const Point & o) {
        if(sgn(x-o.x) != 0) return sng(x-o.x) < 0;
        return sgn(y-o.y) < 0;
    }
};

template<class T> struct Circle {
    Point<T> c;
    T r;

    Circle(Point<T> x, T raio) : c(x), r(raio) {}

    bool contain(Point<T> p) const {
        T d = (p.x-c.x)*(p.x-c.x) + (p.y-c.y)*(p.y-c.y);
        // colocar <=0 caso a borda conte como dentro do circulo
        return sgn(d-r*r)<0;
    }
};


void test() {
    int l, w, h, o;
    while(cin >> l >> w >> h >> o) {
        ld vol = l*w*h;
        // dbg(atan2(h,l));
        if(sgn(rad(o)-atan2(h,l))<=0){
            ld ro = rad(o);
            ld H = l/cosl(ro);
            ld x = H*H-l*l;
            x = sqrtl(x);
            cout<<vol-x*l/2.0l*w<<" mL"<<el;
        }
        else{
            o = 90-o;
            ld ro = rad(o);
            ld H = h/cosl(ro);
            // dbg(H);
            ld x = H*H-h*h;
            x = sqrtl(x);
            cout<<x*h/2.0l*w<<" mL"<<el;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(3);

    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
