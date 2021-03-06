/*
CF-8-16 Something
*/
#include <cstdio>
#include <cstring>
using namespace std;
int n, k, d, t;
#define N 1000005
int a[N], b[N], c[N];
char ch[N], ans[N];

void mul(int* a, int* b){
    for (int i = 0; i < n; ++ i){
        c[i] = b[a[i]];
    }
    for (int i = 0; i < n; ++ i){
        a[i] = c[i];
    }
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%s", ch);
    n = strlen(ch);
    scanf("%d", &t);
    while (t--){
        scanf("%d%d", &k, &d);
        int now = 0;
        for (int i = 0; i < d; ++ i){
            for (int j = i; j < k; j += d){
                a[j] = now ++;
            }
        }
        for (int i = k; i < n; ++ i){
            a[i] = i;
        }
        for (int i = 0; i < n; ++ i){
            a[i] = (a[i] - 1 + n) % n;
        }

        for (int i = 0; i < n; ++ i){
            b[i] = i;
        }
        now = (n - k + 1);
        while (now){
            if (now & 1){
                mul(b, a);
            }
            mul(a, a);
            now >>= 1;
        }
        for (int i = 0; i < n; ++ i){
            ans[(b[i] + n - k + 1) % n] = ch[i];
        }
        for (int i = 0; i < n; ++ i){
            ch[i] = ans[i];
        }
        printf("%s\n", ch);
    }
    return 0;
}