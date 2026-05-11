// lib de geometria.
/*
  TODO: 
* Colocar coisas dentro da namespace.
* Fazer função para intesecção de círculos.
* Fazer mais testes para testar se isso está funcionando.
*/

using ld = long double;
using ll = long long;

const ld EPS = 1e-8;

// testar o sinal de um numero. Funciona até mesmo quando o tipo é inteiro.
template<typename T> int sgn(T x) { return (x > EPS) - (x < -EPS); }

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
