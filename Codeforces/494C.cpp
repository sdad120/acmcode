/*
CF-8-16 Something
*/
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int n, m;
#define N 5005
int x[N], y[N], z[N], id[N];
vector<int> e[N];
double p[N];
int a[100005], t[400005], now;
double dp[N][N*2];
bool vis[N][N*2];

int cmp(int a, int b){
    return y[a] - x[a] < y[b] - x[b];
}

int get(int k, int l, int r, int x, int y){
    if (l == x && r == y){
        return t[k];
    }
    int mid = (l + r) / 2;
    if (y <= mid) return get(k*2, l, mid, x, y);
    else if (x > mid) return get(k*2+1, mid+1, r, x, y);
    else return max(get(k*2, l, mid, x, mid), get(k*2+1, mid+1, r, mid+1, y));
}

void bld(int k, int l, int r){
    if (l == r){
        t[k] = a[l] - now + 5000;
        return;
    }
    int mid = (l + r) / 2;
    bld(k*2, l, mid);
    bld(k*2+1, mid+1, r);
    t[k] = max(t[k*2], t[k*2+1]);
}

double dfs(int k, int up){
    if (vis[k][up]) return dp[k][up];
    vis[k][up] = 1;
    dp[k][up] = 0;
    double tmp = p[k];
    for (int i = 0; i < e[k].size(); ++ i){
        tmp *= dfs(e[k][i], up-1);
    }
    if (z[k] + 1 <= up) dp[k][up] = tmp;
    tmp = 1 - p[k];
    for (int i = 0; i < e[k].size(); ++ i){
        tmp *= dfs(e[k][i], up);
    }
    if (z[k] <= up) dp[k][up] += tmp;
    return dp[k][up];
}

int main(){
 //   freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    now = 0;
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        now = max(now, a[i]);
    }
    for (int i = 1; i <= m; ++ i){
        scanf("%d%d%lf", &x[i], &y[i], &p[i]);
        id[i] = i;
    }
    sort(id + 1, id + m + 1, cmp);
    x[m+1]  = 1; y[m+1] = n; p[m+1] = 0; id[m+1] = m + 1;
    for (int i = 1; i <= m; ++ i){
        for (int j = i + 1; j <= m + 1; ++ j){
            if (x[id[i]] >= x[id[j]] && y[id[i]] <= y[id[j]]){
                e[id[j]].push_back(id[i]);
                break;
            }
        }
    }
    bld(1, 1, n);
    for (int i = 1; i <= m + 1; ++ i){
        z[i] = get(1, 1, n, x[i], y[i]);
    }
    double ans = 0;
    for (int up = 5000; up <= 5000 + m; ++ up){
        dfs(m + 1, up);
        ans += 1.0 * (up - 5000 + now) * (dp[m+1][up] - dp[m+1][up-1]);
    }
    printf("%.10f\n", ans);
    return 0;
}