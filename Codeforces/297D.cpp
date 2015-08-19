/*
CF-8-16 Something
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, k;
char h[1005][1005], v[1005][1005];
char th[1005][1005], tv[1005][1005];
int a[1005][1005];

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < 2 * n - 1; ++ i){
        if (i & 1) scanf("%s", v[i/2]); else scanf("%s", h[i/2]);
    }
    if (k == 1){
        int sum = 0;
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m - 1; ++ j){
                sum += h[i][j] == 'N';
            }
        }
        for (int i = 0; i < n - 1; ++ i){
            for (int j = 0; j < m; ++ j){
                sum += v[i][j] == 'N';
            }
        }
        int tot = n * (m - 1) + (n - 1) * m;
        if (tot > 4 * sum){
            puts("YES");
            for (int i = 0; i < n; ++ i){
                for (int j = 0; j < m; ++ j){
                    printf("1%c", j == m - 1 ? '\n' : ' ');
                }
            }
        } else {
            puts("NO");
        }
        return 0;
    }
    int flag = 0;
    if (n > m){
        flag = 1;
        for (int i = 0; i < n - 1; ++ i){
            for (int j = 0; j < m; ++ j){
                th[j][i] = v[i][j];
            }
        }
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m - 1; ++ j){
                tv[j][i] = h[i][j];
            }
        }
        swap(n, m);
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < m; ++ j){
                h[i][j] = th[i][j];
                v[i][j] = tv[i][j];
            }
        }
    }
    for (int i = 0; i < n; ++ i){
        int sum = 0;
        for (int j = -1; j < m - 1; ++ j){
            if (j == -1){
                a[i][j+1] = 1;
            } else
            if (h[i][j] == 'E'){
                a[i][j+1] = a[i][j];
            } else {
                a[i][j+1] = 3 - a[i][j];
            }
            if (i){
                if (v[i-1][j+1] == 'E' && a[i][j+1] != a[i-1][j+1]){
                    sum ++;
                }
                if (v[i-1][j+1] == 'N' && a[i][j+1] == a[i-1][j+1]){
                    sum ++;
                }
            }
        }
        if (sum > m / 2){
            for (int j = 0; j < m; ++ j){
                a[i][j] = 3 - a[i][j];
            }
        }
    }
    puts("YES");
    if (flag)
    for (int i = 0; i < m; ++ i){
        for (int j = 0; j < n; ++ j){
            printf("%d%c", a[j][i], j == n - 1 ? '\n' : ' ');
        }
    } else 
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < m; ++ j){
            printf("%d%c", a[i][j], j == m - 1 ? '\n' : ' ');
        }
    }
    return 0;
}