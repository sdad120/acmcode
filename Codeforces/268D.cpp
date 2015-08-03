/*
CF-8-2 Something
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;
int ans, d[205][205];
int q[50005], p[205], x[50005], y[50005], z[50005];
vector<int> e[205], w[205];

void spfa(int i){
    for (int j = 0; j < n; ++ j){
        d[i][j] = 100000000;
        p[j] = 0;
    }
    int l = 0, r = 1;
    q[1] = i;
    p[i] = 1;
    d[i][i] = 0;
    while (l < r){
        int k = q[++l];
        p[k] = 0;
        for (int j = 0; j < e[k].size(); ++ j){
            int u = e[k][j];
            if (w[k][j] + d[i][k] < d[i][u]){
                d[i][u] = w[k][j] + d[i][k];
                if (p[u] == 0){
                    p[u] = 1;
                    q[++r] = u;
                }
            }
        }
    }
}

int L[205], R[205], id[205];

int cmp(int x, int y){
    if (R[x] == R[y]){
        return L[x] < L[y];
    }
    return R[x] < R[y];
}

int ok(int dist){
    for (int i = 0; i < m; ++ i){
        for (int j = 0; j < n; ++ j){
            int dist1 = dist - d[x[i]][j];
            int dist2 = dist - d[y[i]][j];
            R[j] = min(z[i], dist1);
            L[j] = max(z[i]-dist2, 0);
            id[j] = j;
        }
        sort(id, id + n, cmp);
        int now = L[id[0]];
        for (int j = 0; j < n; ++ j){
            if (R[id[j]] >= 0 && now <= R[id[j]]){
                return 1;
            }
            now = max(now, L[id[j]]);
        }
        if (now <= z[i]) return 1;
    }
    return 0;
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i){
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
        -- x[i]; -- y[i]; z[i] *= 2;
        e[x[i]].push_back(y[i]);
        e[y[i]].push_back(x[i]);
        w[x[i]].push_back(z[i]);
        w[y[i]].push_back(z[i]);
    }
    for (int i = 0; i < n; ++ i){
        spfa(i);
    }
    int l = 0, r = 100000000;
    while (l < r){
        int mid = (l + r) / 2;
        if (ok(mid)) r = mid; else l = mid + 1;
    }
    printf("%.10f\n", l / 2.0);
    return 0;
}
