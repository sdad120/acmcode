/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
const int mo = 1e9 + 7;
long long dp[205][205];

struct point{
    int x, y;
    void input(){
        scanf("%d%d", &x, &y);
    }
    point operator-(const point &a){
        point ret;
        ret.x = x - a.x;
        ret.y = y - a.y;
        return ret;
    }
}p[205];

long long cross(point a, point b, point c){
    return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (b.y - a.y) * (c.x - a.x);
}

long long dfs(int l, int r){
    if (l + 1 == r){
        dp[l][r] = 1;
    }
    if (dp[l][r] != -1) return dp[l][r];
    dp[l][r] = 0;
    for (int i = l + 1; i < r; ++ i){
        if (cross(p[l], p[r], p[i]) >= 0) continue;
        dp[l][r] = (dp[l][r] + dfs(l, i) * dfs(i, r) % mo) % mo;
    }
    return dp[l][r];
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        p[i].input();
    }
    double ans = 0;
    for (int i = 0; i < n - 1; ++ i){
        ans += cross(p[0], p[i], p[i+1]);
    }
    if (ans < 0){
        reverse(p, p + n);
    }
    memset(dp, -1, sizeof(dp));
    dfs(0, n - 1);
    printf("%d\n", (int)dp[0][n-1]);
    return 0;
}