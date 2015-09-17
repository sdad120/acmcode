
struct tree{

    int cnt, n;
    int t[N], id[N], f[N][20], d[N];
    vector<int> e[N];

    void init(int _n){
        n = _n;
        for (int i = 0; i < n; ++ i){
            e[i].clear();
        }
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < 20; ++ j){
                f[i][j] = -1;
            }
        }
        cnt = 0;
    }

    void dfs(int k){
        t[k] = ++ cnt;
        id[cnt] = k;
        for (int i = 0; i < e[k].size(); ++ i){
            int u = e[k][i];
            if (u == f[k][0]) continue;
            f[u][0] = k;
            for (int j = 1; j < 20; ++ j){
                f[u][j] = f[f[u][j-1]][j-1];
            }
            d[u] = d[k] + 1;
            dfs(u);
        }
    }

    int getLca(int x, int y){
        if (d[x] < d[y]){
            swap(x, y);
        }
        while (d[x] != d[y]){
            for (int i = 19; i >= 0; -- i){
                if (d[x] - (1 << i) >= d[y]){
                    x = f[x][i];
                    break;
                }
            }
        }
        if (x == y) return x;
        while (f[x][0] != f[y][0]){
            for (int i = 19; i >= 0; -- i){
                if (f[x][i] != f[y][i]){
                    x = f[x][i];
                    y = f[y][i];
                    break;
                }
            }
        }
        return f[x][0];
    }
};
