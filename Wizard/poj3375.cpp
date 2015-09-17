#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
#define inf 1684300900
#define N 2005
#define M 100005
int a[M], b[N];
int dp[2][M], f[M];

void get(int k, int &L, int &R){
    int now = lower_bound(a, a + m, b[k]) - a;
    L = max(0, now - n - 50);
    R = min(m - 1, now + n + 50);
}

int main(){
   // freopen("in", "r", stdin);
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++ i){
        scanf("%d", &a[i]);
    }
    sort(a, a + m);
    for (int j = 0; j < n; ++ j){
        scanf("%d", &b[j]);
    }
    sort(b, b + n);
    int L, R;
    get(0, L, R);
    for (int i = L; i <= R; ++ i){
        dp[0][i] = abs(a[i] - b[0]);
        f[i] = (i == L) ? dp[0][i] : min(f[i-1], dp[0][i]);
    }
    int cur = 0;
    for (int i = 1; i < n; ++ i){
        cur = 1 - cur;
        int pL, pR;
        get(i - 1, pL, pR);
        get(i, L, R);
        for (int j = L; j <= R; ++ j){
            int ha = j - 1;
            if (ha > pR) ha = pR;
            if (ha < pL){
                dp[cur][j] = inf;
            } else {
                dp[cur][j] = f[ha] + abs(a[j] - b[i]);
            }
        }
        for (int j = L; j <= R; ++ j){
            f[j] = (j == L) ? dp[cur][j] : min(f[j-1], dp[cur][j]);
        }
    }
    printf("%d\n", f[R]);
    return 0;
}
