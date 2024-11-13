/*
    Struct para criar uma Componente Fortemente Conexa de um grafo dirigido.

    Indexado de 0.

    É bom ver o que você precisa adicionar caso seja necessário. O solve fica a gosto do freguês usar ou não.
*/
struct SCC {
    int n; // tamanho do grafo.
    int n_cond; // tamanho do grafo condensado.

    vector<vector<int>> edges, rEdges; // arestas e arestas reversas.
    vector<vector<int>> cond_graph; // grafo condensado em uma SCC.
    vector<int> order, comp;
    vector<int> root_nodes, roots; // representantes de cada componente e raizes
    vector<bool> vis; // marcar os caras como visitado ou não.
    vector<int> in, out; // indegree e outdegree do grafo condensado.

    SCC () {}

    // já inicializar todos os caras.
    SCC(int n) {
        this->n = n;
        edges.resize(n);
        rEdges.resize(n);
        roots.resize(n);
        in.resize(n);
        out.resize(n);
    }

    // ou se não quiser pode usar init. Fica a gosto do freguês.
    void init(int n) {
        this->n = n;
        edges.resize(n);
        rEdges.resize(n);
        roots.resize(n);
        in.resize(n);
        out.resize(n);
    }

    // dfs para andar nas arestas e arestas reversas do grafo, coletando o que é necessário.
    void dfs(int u, vector<int> &vet, vector<vector<int>> &graph) {
        vis[u] = true;
        for(auto v: graph[u]) {
            if(!vis[v]) dfs(v, vet, graph);
        }
        vet.push_back(u);
    }

    // adicionar arestas u->v e v->u.
    void add_edge(int u, int v) {
        edges[u].push_back(v);
        rEdges[v].push_back(u);
    }

    // função para criar a Componente Fortemente Conexa.
    void initSCC() {
        vis.assign(n, false);
        for(int i=0; i<n; i++){
            if(!vis[i]) dfs(i, order, edges);
        }

        reverse(order.begin(), order.end());

        vis.assign(n, false);
        int color = 0;
        
        for(auto v: order) {
            if(!vis[v]) {
                dfs(v, comp, rEdges);
                root_nodes.push_back(color);
                for(auto u: comp){
                    roots[u] = color;
                }
                color++;
                comp.clear();
            }
        }
        this->n_cond = color;

        cond_graph.resize(n_cond);

        for(int v=0; v<n; v++) {
            for(auto u: edges[v]) {
                if(roots[u] != roots[v]) {
                    cond_graph[roots[v]].push_back(roots[u]);
                    in[roots[u]]++;
                    out[roots[v]]++;
                }
            }
        }
    }

    // função de solve para resolver algo usando a scc.
    int solve() {}
};
