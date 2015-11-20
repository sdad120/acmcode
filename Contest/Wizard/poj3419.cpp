#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define N 200005
#define MAX 1000000
int n, m;
int a[N], right[N], t[N*4], p[N*10];

void bld(int k, int l, int r){
    if (l == r){
        t[k] = right[l] - l + 1;
        return;
    }
    int mid = (l + r) / 2;
    bld(k*2, l, mid);
    bld(k*2+1, mid+1, r);
    t[k] = max(t[k*2], t[k*2+1]);
}

int get(int k, int l, int r, int x, int y){
    if (x <= l && r <= y){
        return t[k];
    }
    int mid = (l + r) / 2, ret = 0;
    if (x <= mid) ret = max(ret, get(k*2, l, mid, x, y));
    if (y > mid) ret = max(ret, get(k*2+1, mid+1, r, x, y));
    return ret;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
    }
    int cntRight = 0;
    for (int left = 1; left <= n; ++ left){
        while (cntRight + 1 <= n && p[a[cntRight+1]+MAX] == 0){
            p[a[++cntRight]+MAX] = 1;
        }
        right[left] = cntRight;
        p[a[left]+MAX] = 0;
    }
    bld(1, 1, n);
    while (m--){
        int x, y;
        scanf("%d%d", &x, &y); ++ x; ++ y;
        int l = x, r = y;
        while (l < r){
            int mid = (l + r) / 2;
            if (right[mid] >= y) r = mid; else l = mid + 1;
        }
        int ans = 0;
        if (right[l] >= y){
            ans = y - l + 1;
        }
        if (l - 1 > 0 && right[l-1] <= y){
            ans = max(ans, get(1, 1, n, x, l - 1));
        }
        printf("%d\n", ans);
    }
    return 0;
}
