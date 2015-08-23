struct spfa{
    #define inf 168430090
    int p[N], n;
    queue<int> q;
    vector<int> e[N], w[N];
    void init(int _n){
        n = _n;
        for (int i = 0; i < n; ++ i){
            e[i].clear();
            w[i].clear();
        }
    }
    void add(int x, int y, int z){
        e[x].push_back(y);
        w[x].push_back(z);
    }
    void solve(int st, int d[]){
        for (int i = 0; i < n; ++ i){
            d[i] = inf;
            p[i] = 0;
        }
        q.push(st);
        d[st] = 0; p[st] = 1;
        while (!q.empty()){
            int k = q.front(); q.pop();
            p[k] = 0;
            for (int i = 0; i < e[k].size(); ++ i){
                int u = e[k][i];
                if (d[u] > d[k] + w[k][i]){
                    d[u] = d[k] + w[k][i];
                    if (p[u] == 0){
                        p[u] = 1;
                        q.push(u);
                    }
                }
            }
        }
    }   
};