/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
using namespace std;
int n, m;
#define N 77777
const int mo = 777777777;
struct mat{
    int a[3][3];
}A[4], s[N*4];
int c[N];
mat ret;

mat mul(const mat&A, const mat&B){
    for (int i = 0; i < 3; ++ i){
        for (int j = 0; j < 3; ++ j){
            ret.a[i][j] = 0;
            for (int k = 0; k < 3; ++ k){
                ret.a[i][j] = (ret.a[i][j] + 1ll * A.a[i][k] * B.a[k][j] % mo) % mo;
            }
        }
    }
    return ret;
}

void bld(int k, int l, int r){
    if (l == r){
        s[k] = A[0];
        return;
    }
    int mid = (l + r) / 2;
    bld(k*2, l, mid);
    bld(k*2+1, mid+1, r);
    s[k] = mul(s[k*2], s[k*2+1]);
}

void add(int k, int l, int r, int x, int y){
    if (l == r){
        s[k] = A[y];
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) add(k*2, l, mid, x, y);
    else if (x > mid) add(k*2+1, mid+1, r, x, y);
    s[k] = mul(s[k*2], s[k*2+1]);
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < 3; ++ i){
        for (int j = 0; j < 3; ++ j){
            scanf("%d", &A[0].a[i][j]);
        }
    }
    for (int k = 1; k <= 3; ++ k){
        memset(A[k].a, 0, sizeof(A[k].a));
        for (int i = 0; i < 3; ++ i){
            A[k].a[i][k-1] = A[0].a[i][k-1];
        }
    }
    if (n > 1) bld(1, 1, n - 1);
    int x, y;
    while (m--){
        scanf("%d%d", &x, &y);
        if (x > 1) add(1, 1, n - 1, x - 1, y);
        c[x] = y;
        int ans = 0;
        for (int i = 1; i <= 3; ++ i){
            if (c[1] > 0 && c[1] != i) continue;
            if (n == 1) ans ++;
            for (int j = 1; j <= 3; ++ j){
                ans = (ans + s[1].a[i-1][j-1]) % mo;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}