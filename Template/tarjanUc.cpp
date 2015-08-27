// no test
struct tarjan_und{
    int pre[N], low[N], f[N], cut[N];
    int cnt, sum, n;
    vector<int> e[N], id[N], bcc[N];
    set<int> tbcc[N];

    void init(int _n){
        n = _n;
        for (int i = 0; i < n; ++ i){
            e[i].clear();
            id[i].clear();
            bcc[i].clear();
            tbcc[i].clear();
            cut[i] = pre[i] = low[i] = 0;
            f[i] = -1;
        }
        cnt = sum = 0;
    }

    void add(int x, int y){
        e[x].push_back(y);
        e[y].push_back(x);
    }

    void dfs(int k, int fa){
        low[k] = pre[k] = ++ cnt;
        int child = 0;
        for (int i = 0; i < e[k].size(); ++ i){
            int u = e[k][i];
            if (u == fa) continue;
            if (!pre[u]){
                child ++;
                dfs(u, k);
                low[k] = min(low[k], low[u]);
                if (low[u] >= pre[k]){
                    cut[k] = 1;
                    if (low[u] > pre[k]){
                        id[u][id[k][i]] = id[k][i] = 0;
                    }
                }
            } else if(pre[u] < pre[k]){
                low[k] = min(low[k], pre[u]);
            }
        }
        if (fa < 0 && child == 1) cut[k] = 0;
    }

    void build(int k, int fa){
        f[k] = sum;
        for (int i = 0; i < e[k].size(); ++ i){
            int u = e[k][i];
            if (u == fa || id[k][i] == 0) continue;
            build(u, k);
        }
    }

    void solve(){
        for (int i = 0; i < n; ++ i){
            if (!pre[i]){
                dfs(i, -1);
            }
        }
        for (int i = 0; i < n; ++ i){
            if (f[i] == -1){
                build(i, -1);
                sum ++;
            }
        }
        for (int i = 0; i < n; ++ i){
            printf("%d %d\n", i, f[i]);
            for (int j = 0; j < e[i].size(); ++ j){
                if (id[i][j]) continue;
                tbcc[f[i]].insert(f[e[i][j]]);
            }
        }
        for (int i = 0; i < sum; ++ i){
            for (set<int>::iterator it = tbcc[i].begin(); it != tbcc[i].end(); ++ it){
                e[i].push_back(*it);
            }
        }
    }
};