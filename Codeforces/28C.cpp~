/*
CF-8-2 Something
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m;
int a[55];
double dp[55][55][55], c[55][55][55];

int main(){
  // freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++ i){
        for (int j = 0; j <= n; ++ j){
            for (int k = 0; k <= j; ++ k){
                c[i][j][k] = 1;
                for (int o = 1; o <= n - j; ++ o){
                    c[i][j][k] *= 1.0 * (m - i) / (m - i + 1);  
                }
                for (int o = 1; o <= j - k; ++ o){
                    c[i][j][k] *= 1.0 * (n - k - o + 1) / (o * (m - i + 1));
                }
            }
        }
    }
    double ans = 0;
    for (int largest = 1; largest <= n; ++ largest){
        dp[largest][0][0] = 1;
        for (int i = 1; i <= m; ++ i){
            for (int j = 0; j <= n; ++ j){
                for (int k = max(0, j-a[i]*largest); k <= j; ++ k){
                    dp[largest][i][j] += dp[largest][i-1][k] * c[i][j][k];
                }
            }
        }
        ans += (dp[largest][m][n] - dp[largest-1][m][n]) * largest;
    }
    printf("%.10f\n", ans);
    return 0;
}
