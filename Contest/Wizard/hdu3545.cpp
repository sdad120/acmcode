#include <cstdio>
#include <cstring>
using namespace std;
int n, m;
const int mo = 1e5;
int dp[16][16][16][16];
int vis[16][16][16][16];
int p[4], op[4], ret[5];

int main(){
  //  freopen("in", "r", stdin);
    int _, __ = 0;
    scanf("%d", &_);
    while(_--){
        scanf("%d%d", &n, &m);
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < m; ++ i){
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2); -- x1; -- x2; 
            for (p[0] = 0; p[0] <= n; ++ p[0]){
                for (p[1] = 0; p[1] <= n; ++ p[1]){
                    for (p[2] = 0; p[2] <= n; ++ p[2]){
                        for (p[3] = 0; p[3] <= n; ++ p[3]){
                            if ((p[x1] < y1) ^ (p[x2] < y2)){
                                vis[p[0]][p[1]][p[2]][p[3]] = 1;
                            }
                        }
                    }
                }
            }
        }

        dp[0][0][0][0] = 1;
        for (int color = 0; color <= 255; ++ color){
            for (int k = 0; k < 4; ++ k){
                for (p[0] = 0; p[0] <= n; ++ p[0]){
                    for (p[1] = 0; p[1] <= n; ++ p[1]){
                        for (p[2] = 0; p[2] <= n; ++ p[2]){
                            for (p[3] = 0; p[3] <= n; ++ p[3]){
                                if (p[k] == 0) continue;
                                int &x = dp[p[0]][p[1]][p[2]][p[3]];
                                p[k] --;
                                x = (x + dp[p[0]][p[1]][p[2]][p[3]]) % mo;
                                p[k] ++;
                            }
                        }
                    }
                }               
            }
            for (p[0] = 0; p[0] <= n; ++ p[0]){
                for (p[1] = 0; p[1] <= n; ++ p[1]){
                    for (p[2] = 0; p[2] <= n; ++ p[2]){
                        for (p[3] = 0; p[3] <= n; ++ p[3]){
                            int &x = dp[p[0]][p[1]][p[2]][p[3]];
                            if (vis[p[0]][p[1]][p[2]][p[3]]) x = 0;
                        }
                    }
                }
            }
        }

        int ans = dp[n][n][n][n];
        memset(ret, 0, sizeof(ret));
        int siz = 0;
        while (ans){
            ret[siz++] = ans % 10;
            ans /= 10;
        }
        printf("Case %d: ", ++ __);
        for (int i = 4; i >= 0; -- i){
            printf("%d", ret[i]);
        }
        puts("");
    }
    return 0;
}
