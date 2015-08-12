/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
#define N 1005
int a[N], b[N], s[N];
int k[N][N], vis[N][N], right[N];
long long dp[N][N];
double f[N][N], F[N][N];

int all[N], tot;

double calc(int a, int b, int c, int s){
    double ret = 1;
    for (int i = 1; i <= a; ++ i){
        ret *= 1.0 * (a + c - i + 1) / (s - i + 1);
    }
    for (int i = 1; i <= c; ++ i){
        ret *= 1.0 * (b - i + 1) / (s - a + 1 - i);
    }
    return ret;
}

// long long DP(int k, int n){
//  if (vis[k][n]) return dp[k][n];
//  vis[k][n] = 1;
//  if (k == m){
//      return (n == 0) ? dp[k][n] = 1 : dp[k][n] = 0;
//  }
//  for (int i = 0; i <= min(n, b[k]); ++ i){
//      dp[k][n] += DP(k + 1, n - i);
//  }
//  return dp[k][n];
// }

double get(int k, int n, int i){
    if (right[k+1] < n - i || right[k] < n) return 0;
    if (right[k] == right[k+1]){
        return 1;
    } else
    if (i == 0){
        return 1.0 * (right[k] - n) / right[k];
    } else {
        return 1.0 * n / right[k];
    }
}

double FUN(int k, int n){
    if  (vis[k][n]) return F[k][n];
    vis[k][n] = 1;
    if (k == m){
        return (n == 0) ? F[k][n] = 1 : F[k][n] = 0;
    }
    for (int i = 0; i <= min(n, b[k]); ++ i){
        F[k][n] += f[k][i] * 1.0 * get(k, n, i) * FUN(k + 1, n - i);
    }
    return F[k][n];
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i){
        scanf("%d", &s[i]);
        for (int j = 0; j < s[i]; ++ j){
            scanf("%d", &k[i][j]);
            all[tot++] = k[i][j];
        }
    }
    sort(all, all + tot);
    int now = all[tot-n];
    for (int i = 0; i < m; ++ i){
        for (int j = 0; j < s[i]; ++ j){
            if(k[i][j] == now){
                b[i] ++;
            }
            if (k[i][j] > now){
                a[i] ++;
            }
        }
        for (int j = 0; j <= s[i]; ++ j){
            f[i][j] = calc(a[i], b[i], j, s[i]);
        }
        n -= a[i];
    }
    // memset(vis, 0, sizeof(vis));
    // DP(0, n);
    for (int i = m - 1; i >= 0; -- i){
        right[i] = right[i+1] + b[i];
    }
    memset(vis, 0, sizeof(vis));
    printf("%.10f\n", FUN(0, n));
    return 0;
}