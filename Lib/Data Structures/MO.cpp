/*
    MO data structure to solve problems that revolves around MO algorithm. Pretty easy to use, u can just copypaste and use it as a blackbox, only changing the
    add, remove and calc function. Sometimes u may need to change vector<int> rs to some other type, but u can manage it.
*/

struct query{
    static const int K = 350;
    int l, r, idx;

    query(int _l, int _r, int _idx) { // thing so you can emplace_back
        this->l = _l;
        this->r = _r;
        this->idx = _idx;
    }

    bool operator <(const query &o){
        if(l/K == o.l/K){
            if((l/K)&1){
                return r > o.r;
            }
            return r<o.r;
        }
        return l/K<o.l/K;
    }
};

struct MO{
    /*
        In here we can change everything. Add more things if you think it is necessary for solving your problem, be it more variables, vectors and such.
    */
    vector<query> queries;
    vector<int> rs;

    MO(vector<query> queries){
        this->queries = queries;
    }

    void add(int x){
      
    }

    void rmv(int x){
      
    }

    int calc(){
      
    }

    void run(){
        sort(all(queries));
        rs.resize(queries.size());

        int i = 0, j = -1; // j is always less than i by one in the beginning.
        for(auto [l, r, idx]: queries){ // ALWAYS do j before i, unless u really like getting runtime errors.
            while(j < r){
                j++;
                add(a[j]);
            }

            while(j > r){
                rmv(a[j]);
                j--;
            }

            while(i > l){
                i--;
                add(a[i]);
            }

            while(i < l){
                rmv(a[i]);
                i++;
            }

            rs[idx]=calc();
        }
    }
};
