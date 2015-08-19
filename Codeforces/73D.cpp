/*
CF-8-16 Something
*/
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 1000005
int n, m, k;
int f[N], s[N];

int getf(int x){
    return f[x] == x ? x : f[x] = getf(f[x]);
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++ i){
        f[i] = i;
        s[i] = 1;
    }
    int x, y;
    for (int i = 0; i < m; ++ i){
        scanf("%d%d", &x, &y); -- x; -- y;
        int tx = getf(x), ty = getf(y);
        if (tx != ty){
            f[tx] = ty;
            s[ty] += s[tx];
        }
    }
    int A = 0, B = 0, C = 0;
    for (int i = 0; i < n; ++ i){
        if (f[i] == i){
            if (k < s[i]) s[i] = k;
            if (s[i] == 1){
                A ++;
            } else {
                B ++; C += s[i];
            }
        }
    }
    if (k == 1){
        printf("%d\n", max(0, A + B - 2));
    } else
    if (A == 0){
        puts("0");
    } else {
        if (C - B * 2 + 2 >= A){
            puts("0");
        } else {
            printf("%d\n", (A - (C - B * 2 + 2) + 1) / 2);
        }
    }
    return 0;
}