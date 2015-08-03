/*
CF-8-2 Something
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, k;
const int mo = 1e9 + 7;
#define N 1000005
int p[N], two[N];

int main(){
 //   freopen("in", "r", stdin);
    two[0] = 1;
    for (int i = 1; i < N; ++ i){
        two[i] = (1ll * two[i-1] * 2) % mo;
    }
    int flag = 1, last = 0, first = 0;
    scanf("%d%d%d", &n, &m, &k);
    int x, y;
    for (int i = 0; i < m; ++ i){
        scanf("%d%d", &x, &y);
        if (y != x + 1){
            if (y != x + k + 1){
                flag = 0;
                continue;
            }
            p[x] = 1;
            last = x;
            if (first == 0) first = x;
        }
    }
    if (last){
        for (int i = 1; i <= n; ++ i){
            p[i] += p[i-1];
        }
        if (p[max(0, last-k-1)] > 0){
            flag = 0;
        }
    }
    if (flag == 0){
        puts("0");
        return 0;
    }
    int ans = 0;
    if (last == 0){
        ans = 1;
        for (int i = 1; i + k + 1 <= n; ++ i){
            ans = (ans + two[min(n-k-1, i+k)-i]) % mo;
        }
    } else {
        ans = two[min(n-k-1,first+k)-first-p[last]+1] % mo;
        for (int i = max(1, last-k); i < first; ++ i){
            if (min(n-k-1,i+k)-i-p[last] >= 0)
                ans = (ans + two[min(n-k-1,i+k)-i-p[last]]) % mo;
        }
    }
    printf("%d\n", ans);
    return 0;
}
