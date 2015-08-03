/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
int n, m;
long long k;
int a[205], id[205];
unsigned long long dp[205][205];
char ans[205];

int cmp(int x, int y){
    return a[x] < a[y];
}

int main(){
 //   freopen("in", "r", stdin);
    cin >> n >> m >> k;
    int x;
    memset(a, 10, sizeof(a));
    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= m; ++ j){
            cin >> x;
            if (x < a[i + j - 1]) a[i + j - 1] = x;
        }
    }
    for (int i = 1; i < n + m; ++ i){
        id[i] = i;
    }
    sort(id + 1, id + n + m - 1, cmp);

    for (int now = 1; now < n + m; ++ now){
        ans[id[now]] = '(';
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i < n + m; ++ i){
            for (int j = 0; j < n + m; ++ j){
                 if (ans[i] == '('){
                    if (j) dp[i][j] += dp[i-1][j-1];
                    if (dp[i][j] > k) dp[i][j] = k;
                 }
                 if (ans[i] == ')'){
                    dp[i][j] += dp[i-1][j+1];
                    if (dp[i][j] > k) dp[i][j] = k;
                 }
                 if (ans[i] == 0){
                    if(j) dp[i][j] += dp[i-1][j-1];
                    if (dp[i][j] > k) dp[i][j] = k;
                    dp[i][j] += dp[i-1][j+1];
                    if (dp[i][j] > k) dp[i][j] = k;
                 }
            }
        }
        if (k > dp[n+m-1][0]){
            k -= dp[n+m-1][0];
            ans[id[now]] = ')';
        }
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= m; ++ j){
            printf("%c", ans[i+j-1]);
        }
        puts("");
    }
    return 0;
}
