/*
CF-8-11 Something
*/
#include <cstdio>
using namespace std;
int n, m;
const int mo = 1e9 + 7;
int dp[2005][2005], s1[2005][2005], s2[2005][2005];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        for (int j = 2; j <= m; ++ j){
            dp[i][j] = (1 + 1ll * s1[i-1][j] * (j + 1) % mo - s2[i-1][j]) % mo;
            s1[i][j] = (s1[i][j-1] + dp[i][j]) % mo;
            s2[i][j] = (s2[i][j-1] + 1ll * dp[i][j] * j % mo) % mo;
        }
    }
    int ans = 0;
    for (int d = 1; d <= n; ++ d){
        for (int k = 2; k <= m; ++ k){
            ans = (ans + 1ll * (m - k + 1) * (dp[d][k] - dp[d-1][k]) % mo * dp[n-d+1][k] % mo) % mo;
        }
    }
    if (ans < 0) ans += mo;
    printf("%d\n", ans);
    return 0;
}