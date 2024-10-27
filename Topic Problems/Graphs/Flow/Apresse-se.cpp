#include <bits/stdc++.h>
using namespace std;

#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdb = pair<ld,ld>;

// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T, typename T1>
ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1>
istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}

const int MOD = 1e9 + 7;

struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi &operator+=(mi &a, mi b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
mi &operator-=(mi &a, mi b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v * b.v); }
mi &operator*=(mi &a, mi b) { return a = a * b; }
mi mypow(mi a, long long p) {
    assert(p >= 0);
    return p == 0 ? 1 : mypow(a * a, p / 2) * (p & 1 ? a : 1);
}
mi inv(mi a) {
    assert(a.v != 0);
    return mypow(a, MOD - 2);
}
mi operator/(mi a, mi b) { return a * inv(b); }

#pragma endregion

// [T -> Fluxo, T2 -> Custo]
template <class T = ll, class T2 = ll>
class MCMF {
public:
    struct Edge {
        Edge(int a, T b, T2 c) : to(a), cap(b), cost(c) {}
        int to;
        T cap;
        T2 cost;
    };

    MCMF(int size) {
        n = size;
        edges.resize(n);
        pot.assign(n, 0);
        dist.resize(n);
        visit.assign(n, false);
    }

    pair<T, T2> mcmf(int src, int sink) {
        pair<T, T2> ans(0, 0);
        if(!SPFA(src, sink)) return ans;
        fixPot();

        while(SPFA(src, sink)) {
            auto flow = augment(src, sink);
            ans.first += flow.first;
            ans.second += flow.first * flow.second;
            fixPot();
        }
        return ans;
    }

    void addEdge(int from, int to, T cap, T2 cost) {
        edges[from].push_back(list.size());
        list.push_back(Edge(to, cap, cost));
        edges[to].push_back(list.size());
        list.push_back(Edge(from, 0, -cost));
    }
private:
    int n;
    vector<vector<int>> edges;
    vector<Edge> list;
    vector<int> from;
    vector<T2> dist, pot;
    vector<bool> visit;

    pair<T, T2> augment(int src, int sink) {
        pair<T, T2> flow = {list[from[sink]].cap, 0};
        for(int v = sink; v != src; v = list[from[v]^1].to) {
            flow.first = min(flow.first, list[from[v]].cap);
            flow.second += list[from[v]].cost;
        }
        for(int v = sink; v != src; v = list[from[v]^1].to) {
            list[from[v]].cap -= flow.first;
            list[from[v]^1].cap += flow.first;
        }
        return flow;
    }

    queue<int> q;
    bool SPFA(int src, int sink) {
        T2 INF = numeric_limits<T2>::max();
        dist.assign(n, INF);
        from.assign(n, -1);
        q.push(src);
        dist[src] = 0;
        while(!q.empty()) {
            int on = q.front();
            q.pop();
            visit[on] = false;
            for(auto e : edges[on]) {
                auto ed = list[e];
                if(ed.cap == 0) continue;
                T2 toDist = dist[on] + ed.cost + pot[on] - pot[ed.to];
                if(toDist < dist[ed.to]) {
                    dist[ed.to] = toDist;
                    from[ed.to] = e;
                    if(!visit[ed.to]) {
                        visit[ed.to] = true;
                        q.push(ed.to);
                    }
                }
            }
        }
        return dist[sink] < INF;
    }

    void fixPot() {
        T2 INF = numeric_limits<T2>::max();
        for(int i = 0; i < n; i++) {
            if(dist[i] < INF) pot[i] += dist[i];
        }
    }
};

struct peixe {
    int x, y;
    double speed;

    peixe (int x, int y, double speed) {
        this->x = x;
        this->y = y;
        this->speed = speed;
    }
};

double dist(pdb a, pdb b) {
    return sqrt((a.ft-b.ft)*(a.ft-b.ft) + (a.sd-b.sd)*(a.sd-b.sd));
}

void test() {
    /*
        This problem reduces to a matching problem with costs, so using a flow algorithm that supports a cost (MCMF, Hungarian)
        is enough to solve this problem. The cost is the euclidean distance of the points, so you just add the edges and run
        the algorithm.
    */

    int n, m;
    while(cin >> n >> m && (n || m)) {
        MCMF<int, double> d(n+m+10);
        int source = m+n+5, sink = m+n+6;
        vector<peixe> a;

        for(int i=0; i<n; i++) { // ler as pessoas
            int x, y;
            double speed;
            cin >> x >> y >> speed;
            a.eb(x, y, speed);
            d.addEdge(source, i+1, 1, 0.0);
        }

        for(int i=1; i<=m; i++) { // ler os pontos de chegada.
            int x, y;
            cin >> x >> y;
            int c;
            vector<int> tmp;
            while(cin>>c && c){
                tmp.pb(c);
            }

            for(int j=0; j<tmp.size(); j++){
                c=tmp[j];
                d.addEdge(c, n+i, 1, dist(mp(x, y), mp(a[c-1].x, a[c-1].y))/ a[c-1].speed);
            }

            d.addEdge(n+i, sink, 1, 0.0);
        }

        auto rs = d.mcmf(source, sink);
        cout<<rs.sd<<"\n";
    }
}
 
int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(1);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
