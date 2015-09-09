#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
double dp[305][305][2][2];
double p[305];

class Bitwisdom{
public:
    double expectedActions(vector<int> _p){
        int n = _p.size();
        for (int i = 0; i < n; ++ i){
            p[i] = _p[i] / 100.0;
        }
        dp[0][1][1][1] = p[0];
        dp[0][0][0][0] = 1 - p[0];
        for (int i = 1; i < n; ++ i){
            for (int j = 0; j <= n; ++ j){
                for (int k = 0; k < 2; ++ k){
                    dp[i][j][1][k] = dp[i-1][j][1][k];
                    if (j) dp[i][j][1][k] += dp[i-1][j-1][0][k];
                    dp[i][j][1][k] *= p[i];
                    dp[i][j][0][k] = dp[i-1][j][0][k] + dp[i-1][j][1][k];
                    dp[i][j][0][k] *= (1 - p[i]);
                }
            }
        }
        // double ret = 0;
        // for (int i = 0; i <= n; ++ i){
        //     for (int j = 0; j < 2; ++ j){
        //         for (int k = 0; k < 2; ++ k){
        //             ret += dp[n-1][i][j][k];
        //             printf("%d %d %d %.5f\n", i, j, k, ret);
        //         }
        //     }
        // }
        // printf("%.5f\n", ret);
        double ans = 0;
        for (int i = 1; i <= n; ++ i){
            if (i == 1) ans += dp[n-1][i][1][1];
            else ans += dp[n-1][i][1][1] * (2 * i - 2);
            ans += (dp[n-1][i][1][0] + dp[n-1][i][0][1]) * (2 * i - 1);
            ans += dp[n-1][i][0][0] * 2 * i;
        }
        return ans;
    }
};