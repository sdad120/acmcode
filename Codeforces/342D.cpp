/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
const int mo = 1e9 + 7;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
char a[5][10005];
int dp[10005][10], p[10005];
int cx[10], cy[10];
int ox, oy;
int e[10][10];

void dfs(int i, int from, int x, int to){
    if (x > 3){
        dp[i+1][to] = (dp[i+1][to] + dp[i][from]) % mo;
        //printf("%d %d %d\n", i, from, to);
        return;
    }
    if (from & (1 << (x - 1))){
        dfs(i, from, x + 1, to);
    } else {
        if (x < 3 && a[x][i+1] == '.' && a[x+1][i+1] == '.' && (from & (1 << x)) == 0){
            dfs(i, from, x + 2, to);
        }
        if (a[x][i+1] != '.'){
            dfs(i, from, x + 1, to);
        } else {
            dfs(i, from, x + 1, to + (1 << (x - 1)));
        }
    }
}


int get(){
    memset(p, 0, sizeof(p));
    for (int i = 1; i <= 3; ++ i){
        for (int j = 1; j <= n; ++ j){
            if (a[i][j] == 'X'){
                p[j] += (1 << (i - 1));
            }
        }
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++ i){
        for (int from = 0; from < 8; ++ from){
            if (dp[i][from] == 0) continue;
            if (p[i+1] & from) continue;
            dfs(i, from, 1, 0);
        }
    }
    return dp[n][0];
}

int main(){
    //freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= 3; ++ i){
        scanf("%s", a[i] + 1);
        for (int j = 1; j <= n; ++ j){
            if (a[i][j] == 'O'){
                ox = i; oy = j;
                a[i][j] = 'X';
            }
        }
    }
    //printf("%d\n", get());
    int ans = 0;
    for (int ost = 1; ost < 16; ++ ost){
        int flag = 1, tot = 0, sign = -1;
        for (int i = 0; i < 4; ++ i){
            if (ost & (1 << i)){
                for (int d = 1; d <= 2; ++ d){
                    int tx = ox + d * dx[i];
                    int ty = oy + d * dy[i];
                    if (tx < 1 || ty < 1 || tx > 3 || ty > n || a[tx][ty] != '.'){
                        flag = 0;
                        break;
                    }
                    cx[tot] = tx; cy[tot] = ty;
                    tot ++;
                }
                sign = (sign == 1) ? -1 : 1;
            }
        }
        if (flag == 0) continue;
        for (int i = 0; i < tot; ++ i){
            a[cx[i]][cy[i]] = 'X';
        }

        ans = (ans + sign * get()) % mo;

        for (int i = 0; i < tot; ++ i){
            a[cx[i]][cy[i]] = '.';
        }
    }
    if (ans < 0) ans += mo;
    printf("%d\n", (int) ans);
    return 0;
}