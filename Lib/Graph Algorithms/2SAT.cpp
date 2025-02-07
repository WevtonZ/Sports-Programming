/*
    0 indexed.

    Struct to solve problems related to 2SAT. It is quite the same everywhere you go but if it is needed to change
    then you can change it. I don't know what though.
*/
struct SAT{
    int nodes; // number of nodes in the graph.
    vector<vector<int>> adj, r_adj; // adjacency and reverse adjacency list for storing vertices.
    vector<bool> vis; // to mark if I visited some node.
    vector<int> comp, order; // components and the order which I will traverse the graph.
    vector<bool> ans; // generates any valid answer.

    SAT(int n) : nodes(n){
        adj.resize(nodes+10);
        r_adj.resize(nodes+10);
        comp.assign(nodes+10, 0);
        ans.assign(nodes+10,false);
    }

    void dfs1(int u){
        vis[u]=true;
        for(auto v: adj[u]){
            if(!vis[v]) dfs1(v);
        }
        order.push_back(u);
    }

    void dfs2(int u, int c){
        comp[u] = c;
        for(auto v: r_adj[u]){
            if(comp[v] == 0)
                dfs2(v,c);
        }
    }

    // add implication u -> v
    void add_imp(int u, int v){
        adj[u].push_back(v);
        r_adj[v].push_back(u);
    }

    // u -> !u
    int neg(int u){
        return (u^1);
    }

    // (a v b) == (!a -> b) & (!b -> a)
    void add_or(int u, bool bu, int v, bool bv){
        u = (2*u)|bu;
        v = (2*v)|bv;

        add_imp(neg(u),v);
        add_imp(neg(v),u);
    }

    // ng == 0 -> (a | b) && (!b | !a)
    // ng == 1 -> (!a | b) && (a | !b)
    // ng is if you want to negate the xor value.
    void add_xor(int u, int v, bool ng){
        if(ng == 0){
            add_or(u,0,v,0);
            add_or(v,1,u,1);
        }
        else{
            add_or(u,1,v,0);
            add_or(u,0,v,1);
        }
    }

    // go for the solve!
    bool solve(){
        vis.assign(nodes,false);
        for(int i = 0; i < nodes; i++){
            if(!vis[i]) dfs1(i);
        }

        int color = 1;

        reverse(order.begin(), order.end());
        for(auto i: order){
            if(comp[i] == 0){
                dfs2(i, color);
                color++;
            }
        }

        for(int i = 0; i < nodes/2; i++){
            int v = (i<<1);
            if(comp[v] == comp[v+1]){
                return false;
            }
            ans[i] = comp[v] > comp[v+1];
        }

        return true;
    }
};
