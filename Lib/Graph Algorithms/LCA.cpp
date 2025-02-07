/*
    Indexado de 1.
    Essa é uma estrutura de LCA padrão. Pode ser feito qualquer modificação para resolver algum problema
    proposto que use LCA, como calcular o máximo em um caminho.
*/
struct LCA {
    int n, K; // quantidade de vértices do grafo / potências de 2 a serem consideradas.
    int timer; // temporizador para contar a entrada e saída de cada vértice.
    vector<vector<int>> & graph; // grafo referenciado para otimizar a velocidade.
    vector<int> dist; // distância entre dois vértices. Pode ser modificado.
    vector<int> in, out; // Tempo de entrada e saída de cada vértice.
    vector<vector<int>> st; // sparse table para calcular os pais em potencia de 2 de cada vertice

    // inicializar a struct de LCA com a qtd de vertices, o grafo e a raiz.
    // raiz padronizada como 1
    LCA(int n, vector<vector<int>> & graph, int root = 1) : n(n), graph(graph) {
        dist.resize(n+10,0);
        in.resize(n+10);
        out.resize(n+10);
        
        timer = 1;
        K = 0;
        while((1 << K) <= n) K++;
        
        // settando o tamanho da sparse table.
        st.resize(n+10);
        for(int i=0; i<=n; i++){
            st[i].resize(K+2);
        }
        build(root, root);
    }

    // criar as coisas
    void build(int u, int ant) {
        in[u] = timer++;
        st[u][0] = ant;
        for(int k=1; k<=K; k++){
            st[u][k] = st[st[u][k-1]][k-1];
        }

        for(int v: graph[u]){
            if(v == ant) continue;
            dist[v] = dist[u] + 1;
            build(v,u);
        }
        out[u] = timer++;
    }

    // u é ancestral de v?
    int is_ancestor(int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    }

    /*
    Funcao para calcular o LCA entre dois vértices.
    */
    int lca(int u, int v) {
        if(is_ancestor(u, v)) return u;
        if(is_ancestor(v, u)) return v;

        for(int i=K; i>=0; i--){
            if(!is_ancestor(st[u][i], v)){
                u = st[u][i];
            }
        }
        return st[u][0];
    }

    // função pra calcular a distância entre dois caras na árvore.
    // é possível só desaparecer com essa função se for necessário.
    int get_dist(int u, int v) {
        return dist[u] + dist[v] - 2*dist[lca(u,v)];
    }
};
