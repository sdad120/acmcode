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
int n;
int xx[1005], yy[1005], x[5005], y[5005], sx, sy;
int vis[5005][5005];
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

void add(int nx, int ny){
    x[++sx] = nx - 1;
    x[++sx] = nx;
    x[++sx] = nx + 1;
    y[++sy] = ny - 1;
    y[++sy] = ny;
    y[++sy] = ny + 1;
}

void dfs(int x, int y){
    vis[x][y] = -1;
    for (int i = 0; i < 4; ++ i){
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (tx >= 0 && ty >= 0 && tx <= sx + 1 && ty <= sy + 1 && vis[tx][ty] == 0){
            dfs(tx, ty);
        }
    }
}

int main(){
 //   freopen("in", "r", stdin);
    scanf("%d", &n);
    int nx = 0, ny = 0;
    char ch[2]; int z;
    add(nx, ny);
    for (int i = 1; i <= n; ++ i){
        scanf("%s%d", ch, &z);
        if (ch[0] == 'R') ny += z;
        if (ch[0] == 'L') ny -= z;
        if (ch[0] == 'U') nx -= z;
        if (ch[0] == 'D') nx += z;
        add(nx, ny);
        xx[i] = nx; yy[i] = ny;
    }       
    sort(x + 1, x + sx + 1); sx = unique(x + 1, x + sx + 1) - x - 1;
    sort(y + 1, y + sy + 1); sy = unique(y + 1, y + sy + 1) - y - 1;
    for (int i = 0; i <= n; ++ i){
        xx[i] = lower_bound(x + 1, x + sx + 1, xx[i]) - x;
        yy[i] = lower_bound(y + 1, y + sy + 1, yy[i]) - y;
    }
    for (int i = 1; i <= n; ++ i){
        if (xx[i] == xx[i-1]){
            for (int j = min(yy[i], yy[i-1]); j <= max(yy[i], yy[i-1]); ++ j){
                vis[xx[i]][j] = 1;
            }
        }
        if (yy[i] == yy[i-1]){
            for (int j = min(xx[i], xx[i-1]); j <= max(xx[i], xx[i-1]); ++ j){
                vis[j][yy[i]] = 1;
            }
        }
    }
    dfs(0, 0);
    long long ans = 0;
    for (int i = 1; i <= sx; ++ i){
        for (int j = 1; j <= sy; ++ j){
            if (vis[i][j] != -1)
                ans += 1ll * (x[i] - x[i-1]) * (y[j] - y[j-1]);
        }
    }
    cout << ans << endl;
    return 0;
}
