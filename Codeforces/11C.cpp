/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t;
int n, m;
char a[255][255];
int right[255][255], down[255][255], xleft[255][255], xright[255][255];
int uright[255][255], udown[255][255], uxleft[255][255], uxright[255][255];
int vis[255][255], lx, ly, rx, ry, size;
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void dfs(int x, int y){
    vis[x][y] = 1;
    size ++;
    lx = min(x, lx);
    ly = min(y, ly);
    rx = max(x, rx);
    ry = max(y, ry);
    for (int d = 0; d < 8; ++ d){
        int tx = dx[d] + x;
        int ty = dy[d] + y;
        if (a[tx][ty] == '1' && vis[tx][ty] == 0) dfs(tx, ty);
    }
}


int main(){
   // freopen("in", "r", stdin);
    scanf("%d", &t);
    while (t--){
        memset(a, 0, sizeof(a));
        memset(vis, 0, sizeof(vis));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i){
            scanf("%s", a[i] + 1);
            for (int j = 1; j <= m; ++ j){
                right[i][j] = down[i][j] = xleft[i][j] = xright[i][j] = 0;
                uright[i][j] = udown[i][j] = uxleft[i][j] = uxright[i][j] = 0;
            }
        }
        for (int i = n; i >= 1; -- i){
            for (int j = m; j >= 1; -- j){
                if (a[i][j] == '0') continue;
                right[i][j] = right[i][j+1] + 1;
                down[i][j] = down[i+1][j] + 1;
                xleft[i][j] = xleft[i+1][j-1] + 1;
                xright[i][j] = xright[i+1][j+1] + 1;
            }
        }
        for (int i = 1; i <= n; ++ i){
            for (int j = 1; j <= m; ++ j){
                if (a[i][j] == '0') continue;
                uright[i][j] = uright[i][j-1] + 1;
                udown[i][j] = udown[i-1][j] + 1;
                uxleft[i][j] = uxleft[i-1][j+1] + 1;
                uxright[i][j] = uxright[i-1][j-1] + 1;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++ i){
            for (int j = 1; j <= m; ++ j){
                if (vis[i][j] || a[i][j] == '0') continue;
                lx = n + 1, ly = m + 1;
                rx = 0, ry = 0; 
                size = 0;
                dfs(i, j);
                if (size < 4) continue;

                if (a[lx][ly] == '1' && a[rx][ry] == '1' && rx - lx == ry - ly){
                    int len = rx - lx + 1;
                    if (size == len * 4 - 4 && right[lx][ly] >= len && down[lx][ly] >= len && uright[rx][ry] >= len && udown[rx][ry] >= len){
                        ans ++;
                        //printf("%d %d %d %d\n", lx, ly, rx, ry);
                    }
                }

                int len = (rx - lx + 2) / 2;
                if (a[lx][ly+len-1] == '1' && a[rx][ly+len-1] == '1' && rx - lx == ry - ly){
                    if (size == len * 4 - 4 && xleft[lx][ly+len-1] >= len && xright[lx][ly+len-1] >= len && uxleft[rx][ly+len-1] >= len && uxright[rx][ly+len-1] >= len){
                        ans ++;
                        //printf("%d %d %d %d\n", lx, ly, rx, ry);
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
