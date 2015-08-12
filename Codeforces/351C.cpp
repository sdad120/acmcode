/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
long long dp[44][44];
int a[22], b[22];
#define inf 1000000000000ll
struct mat{
    long long a[44][44];
}ans, A, ret;

mat mul(const mat&A, const mat&B){
    for (int i = 0; i <= 2 * n; ++ i){
        for (int j = 0; j <= 2 * n; ++ j){
            ret.a[i][j] = inf;
            for (int k = 0; k <= 2 * n; ++ k){
                ret.a[i][j] = min(ret.a[i][j], A.a[i][k] + B.a[k][j]);
            }
        }
    }
    return ret;
}

int get(int l, int r){
    memset(dp, 10, sizeof(dp));
    dp[0][l] = 0;
    for (int i = 1; i <= n; ++ i){
        for (int j = 0; j <= 2 * n; ++ j){
            dp[i][j] = min(dp[i-1][j+1] + b[i-1], dp[i][j]);
            if (j) dp[i][j] = min(dp[i-1][j-1] + a[i-1], dp[i][j]);
        }
    }
    return dp[n][r];
}

int main(){
   // freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++ i){
        scanf("%d", &b[i]);
    }
    for (int i = 0; i <= 2 * n; ++ i){
        for (int j = 0; j <= 2 * n; ++ j){
            A.a[i][j] = get(i, j);
        }
    }
    memset(ans.a, 10, sizeof(ans.a));
    for (int i = 0; i <= 2 * n; ++ i){
        ans.a[i][i] = 0;
    }
    while (m){
        if (m & 1){
            ans = mul(ans, A);
        }
        A = mul(A, A);
        m >>= 1;
    }
    printf("%d\n", (int)ans.a[0][0]);
    return 0;
}