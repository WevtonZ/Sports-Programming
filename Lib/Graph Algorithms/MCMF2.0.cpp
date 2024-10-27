/*
    declaration goes like: MCMF<T, T2> placeholder(size);
    My motivation was that sometimes having flow and cost to be of the same type could be a problem. For example in a matching
    problem where the cost part is a double and flow is int.

    To use this algorithm, just declare the class and add edges and call for the mcmf function.
*/

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
