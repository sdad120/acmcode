#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, c, q;
#define N 105
int color[N][N], up[N][N], down[N][N], right[N][N], left[N][N];
int ans[N];

int getMin(int x, int y){
    return min(min(up[x][y], down[x][y]), min(right[x][y], left[x][y]));
}

void updateRow(int k){
    for (int i = 1; i <= m; ++ i){
        if (color[k][i] == color[k][i-1]){
            left[k][i] = left[k][i-1] + 1;
        } else {
            left[k][i] = 1;
        }
    }
    for (int i = m; i >= 1; -- i){
        if (color[k][i] == color[k][i+1]){
            right[k][i] = right[k][i+1] + 1;
        } else {
            right[k][i] = 1;
        }
    }
}

void updateCol(int k){
    for (int i = 1; i <= n; ++ i){
        if (color[i][k] == color[i-1][k]){
            up[i][k] = up[i-1][k] + 1;
        } else {
            up[i][k] = 1;
        }
    }
    for (int i = n; i >= 1; -- i){
        if (color[i][k] == color[i+1][k]){
            down[i][k] = down[i+1][k] + 1;
        } else {
            down[i][k] = 1;
        }
    }
}

void updateAns(int x, int y, int ty){
    int k = getMin(x, y);
    ans[color[x][y]] += ty * (k - 1);
}

int main(){
 //   freopen("in", "r", stdin);
    scanf("%d%d%d%d", &n, &m, &c, &q);
    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= m; ++ j){
            scanf("%d", &color[i][j]);
        }
    }
    for (int i = 1; i <= n; ++ i){
        updateRow(i);
    }
    for (int i = 1; i <= m; ++ i){
        updateCol(i);
    }

    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= m; ++ j){
            updateAns(i, j, 1);
        }
    }
    while (q--){
        char ch[10];
        int x, y, z;
        scanf("%s", ch);
        if (ch[0] == 'Q'){
            scanf("%d", &x);
            printf("%d\n", ans[x]);
        } else {
            scanf("%d%d%d", &x, &y, &z);
            for (int i = 1; i <= n; ++ i){
                updateAns(i, y, -1);
            }
            for (int i = 1; i <= m; ++ i){
                updateAns(x, i, -1);
            }
            updateAns(x, y, 1);
            color[x][y] = z;
            updateRow(x);
            updateCol(y);
            for (int i = 1; i <= n; ++ i){
                updateAns(i, y, 1);
            }   
            for (int i = 1; i <= m; ++ i){
                updateAns(x, i, 1);
            }
            updateAns(x, y, -1);
        }
    }
    return 0;
}
