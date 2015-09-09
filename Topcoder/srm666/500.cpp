#include <cstdio>
#include <cstring>
using namespace std;
int dp[5005][2][2], c[5005][5005];
int n;
const int mo = 1e9 + 7;

int dfs(int k, int l, int r){
    if (k == 0){
        return 1;
    }
    if (k == 1){
        return n - l - r;
    }
    if (dp[k][l][r] >= 0) return dp[k][l][r];    
    dp[k][l][r] = 0;
    for (int i = 1; i <= k; ++ i){
        int now = n;
        if (i == 1 && l > 0) now --;
        if (i == k && r > 0) now --;
        dp[k][l][r] = (dp[k][l][r] + 1ll * now * c[k-1][i-1] % mo * dfs(i-1, l, 1) % mo * dfs(k-i, 1, r) % mo) % mo;
    }
    return dp[k][l][r];
}

class SumOverPermutations{
public:
    int findSum(int _n){
        n = _n;
        for (int i = 0; i <= n; ++ i){
            c[i][0] = c[i][i] = 1;
            for (int j = 1; j < i; ++ j){
                c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mo;
            }
        }
        memset(dp, -1, sizeof(dp));
        return dfs(n, 0, 0);
    }
};