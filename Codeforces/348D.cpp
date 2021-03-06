/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
using namespace std;
int n, m;
const int mo = 1e9 + 7;
int dp[3005][3005];
char a[3005][3005];

int calc(int x1, int y1, int x2, int y2){
    memset(dp, 0, sizeof(dp));
    if (a[x1][y1] == '#') return 0;
    dp[x1][y1] = 1;
    for (int i = x1; i <= x2; ++ i){
        for (int j = y1; j <= y2; ++ j){
            if (a[i][j] == '#') continue;
            if (i == x1 && j == y1) continue;
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mo;
        }
    }
    return dp[x2][y2];
}

int main(){
   // freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        scanf("%s", a[i] + 1);
    }
    printf("%d\n", (int)(((1ll * calc(2, 1, n, m - 1) * calc(1, 2, n - 1, m) % mo - 1ll * calc(2, 1, n - 1, m) * calc(1, 2, n, m - 1) % mo) + mo) % mo));
    return 0;
}
