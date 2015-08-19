/*
CF-8-16 Something
*/
#include <cstdio>
using namespace std;
int n, m;
#define N 200005
#define MP 193893487
int a[N], b[N], pa[N], pb[N];
int ex[N], pattern, hashval;

struct tree{
    int c[N];
    void add(int x, int y){
        for (int i = x; i <= m; i += i & -i){
            c[i] += y;
        }
    }
    int get(int x){
        int ret = 0;
        for (int i = x; i > 0; i -= i & -i){
            ret += c[i];
        }
        return ret;
    }
}num, val;

void add(int k, int value, int type){
    hashval = hashval + type * (val.get(m) - val.get(k));
    hashval = hashval + type * (num.get(k) + (type == 1)) * value;
    num.add(k, type); val.add(k, type * value);
}

int main(){
   // freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        pa[a[i]] = i;
    }
    for (int i = 1; i <= m; ++ i){
        scanf("%d", &b[i]);
        pb[b[i]] = i;
    }

    ex[0] = 1; 
    for (int i = 1; i < N; ++ i){
        ex[i] = ex[i-1] * MP;
    }
    pattern = hashval = 0;
    for (int i = 1; i <= n; ++ i){
        pattern  += pa[i] * ex[i];
    }
    for  (int i = 1; i <= n; ++ i){
        add(pb[i], ex[i], 1);
    }

    int ans = 0;
    for (int i = 1; i <= m - n + 1; ++ i){
        if (pattern == hashval) ans ++;
        if (i == m - n + 1) break;
        pattern *= MP;
        add(pb[i], ex[i], -1);
        add(pb[i+n], ex[i+n], 1);
    }

    printf("%d\n", ans);
    return 0;
}