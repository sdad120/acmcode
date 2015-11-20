#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100005
int n, a[N], b[N], id[N], afterMax[N];

int ok(int X){
    afterMax[n] = 0;
    for (int i = n - 1; i >= 0; -- i){
        int k = id[i];
        afterMax[i] = max(afterMax[i+1], b[k]);
    }

    if (afterMax[0] <= X) return 1;
    for (int i = 0; i < n; ++ i){
        int need = X - a[id[i]];
        if (afterMax[i+1] <= need) return 1;
    }
    return 0;
}

int cmp(int x, int y){
    return a[x] < a[y];
}

int main(){
 //   freopen("in", "r", stdin);
    int _, __ = 0;
    scanf("%d", &_);
    while (_--){
        scanf("%d", &n);
        for (int i = 0; i < n; ++ i){
            scanf("%d%d", &a[i], &b[i]);
            id[i] = i;
        }
        sort(id, id + n, cmp);
        int l = 0, r = 1e9 * 2;
        while (l < r){
            int mid = (l + r) / 2;
            if (ok(mid)) r = mid; else l = mid + 1;
        }
        printf("Case %d: %d\n", ++__, l);
    }
    return 0;
}
