// https://cses.fi/problemset/task/2189

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back
 
template <class T> struct Point{
    T x, y;
    Point(T a = 0, T b = 0) : x(a), y(b) {}
 
    friend istream &operator>>(istream &is, Point & o){
        cin >> o.x >> o.y;
        return is;
    }
};
 
ll cross(Point<ll> a, Point<ll> b, Point<ll> c){
    return a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y);
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
      Podemos ver se um ponto está acima de uma reta gerada por outros dois usando Cross Product. A ideia é basicamente olhar se o resultado
      do produto é positivo ou negativo. Se for positivo, então o ponto está no sentido anti-horário em relação aos outros dois, logo, está a esquerda dele.
      Os outros casos podem ser analisados da mesma forma.
    */
  
    int t; cin >> t;
    while(t--){
        Point<ll> a, b, c;
        cin >> a >> b >> c;
        ll v = cross(a,b,c);
        if(v>0) cout<<"LEFT\n";
        else if(v<0) cout<<"RIGHT\n";
        else cout<<"TOUCH\n";
    }
 
    return 0;
}
