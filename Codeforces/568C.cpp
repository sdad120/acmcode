/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
int n, m;
int p[30]; // for V -> 1 for C -> 0
char A[30], ch[205];
int d[405][405];
int now[205], minv[205], minc[205];

int fan(int x){
    return (x > n) ? (x - n) : (x + n);
}

int main(){
 //   freopen("in", "r", stdin);
    scanf("%s", A);    
    int tot = strlen(A);
    for (int i = 0; i < tot; ++ i){
        p[i] = A[i] == 'V';
    }
    minv[0] = minc[0] = 26;
    for  (int i = 0; i < tot; ++ i){
        if(p[i]){
            minv[0] = i; break;
        }
    }
    for (int i = 0; i < tot; ++ i){
        if  (p[i] == 0){
            minc[0] = i; break;
        }
    }

    scanf("%d%d", &n, &m);
    int x, y;
    char chx[2], chy[2];
    for (int i = 0; i < m; ++ i){
        scanf("%d%s%d%s", &x, chx, &y, chy);
        if (chx[0] == 'V') x += n;
        if (chy[0] == 'V') y += n;
        d[x][y] = 1;
        d[fan(y)][fan(x)] = 1;
    }
    for (int i = 1; i <= 2 * n; ++ i){
        d[i][i] = 1;
    }
    for (int k = 1; k <= 2 * n; ++ k){
        for (int i = 1; i <= 2 * n; ++ i){
            for (int j = 1; j <= 2 * n; ++ j){
                d[i][j] |= d[i][k] & d[k][j];
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        minv[i] = minv[0];
        minc[i] = minc[0];
        for (int j = 1; j <= n; ++ j){
            if (d[i][j] && d[i][j+n]){
                minc[i] = 26;
            }
            if (d[i+n][j] && d[i+n][j+n]){
                minv[i] = 26;
            }
        }
    }

    scanf("%s", ch + 1);
    for (int i = n + 1; i >= 1; -- i){
        memset(now, -1, sizeof(now));
        int iminv = 26, iminc = 26;

        if (minv[i] != 26)
        for (int j = ch[i] - 'a' + 1; j < tot; ++ j){
            if (p[j]){
                iminv = j; break;
            }
        }
        if  (minc[i] != 26)
        for (int j = ch[i] - 'a' + 1; j < tot; ++ j){
            if (p[j] == 0){
                iminc = j; break;
            }
        }

        int flag = 1;

        for (int j = 1; j < i; ++ j){
            now[j] = ch[j] - 'a';
        }

        for (int j = 1; j < i; ++ j){
            int type = p[now[j]];

            if (type == 0 && minc[j] == 26){
                flag = 0;
                break;
            }

            if (type == 1 && minv[j] == 26){
                flag = 0;
                break;
            }

            for (int k = 1; k <= n; ++ k){
                if (d[j+type*n][k]){
                    if (now[k] != -1){
                        if (p[now[k]] != 0){
                            flag = 0;
                            break;
                        }
                    } else {
                        if (k != i) now[k] = minc[k]; else now[k] = iminc;
                    }
                }
                if (d[j+type*n][k+n]){
                    if (now[k] != -1){
                        if (p[now[k]] != 1){
                            flag = 0;
                            break;
                        }
                    } else {
                        if (k != i)  now[k] = minv[k]; else now[k] = iminv;
                    }
                }
            }
        }

        for (int j = i; j <= n; ++ j){
            if (now[j] != -1) continue;
            if (j != i){
                now[j] = min(minv[j], minc[j]);
            } else {
                now[j] = min(iminv, iminc);
            }
            int type = p[now[j]];

            for (int k = 1; k <= n; ++ k){
                if (d[j+type*n][k]){
                    if (now[k] != -1){
                        if (p[now[k]] != 0){
                            flag = 0;
                            break;
                        }
                    } else {
                        if (k != i) now[k] = minc[k]; else now[k] = iminc;
                    }
                }
                if (d[j+type*n][k+n]){
                    if (now[k] != -1){
                        if (p[now[k]] != 1){
                            flag = 0;
                            break;
                        }
                    } else {
                        if (k != i)  now[k] = minv[k]; else now[k] = iminv;
                    }
                }
            }
        }
        for (int i = 1; i <= n; ++ i){
            if (now[i] == 26){
                flag = 0;
                break;
            }
        }

        if (flag){
            for (int i = 1; i <= n; ++ i){
                printf("%c", now[i] + 'a');
            }
            return 0;
        }
    }
    puts("-1");
    return 0;
}