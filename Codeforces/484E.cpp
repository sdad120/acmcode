/*
CF-8-16 Something
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, nh;
#define N 100005
int h[N], hh[N];
int x[N], y[N], w[N];
int l[N], r[N], mid[N], ret[N];
vector<int> act[N], id[N];

struct sta{
    int s, l, r, len;
}t[N*4];

sta update(const sta&a, const sta&b){
    sta ret;
    ret.len = a.len + b.len;
    if (a.l == a.len){
        ret.l = a.l + b.l;
    } else {
        ret.l = a.l;
    }
    if (b.r == b.len){
        ret.r = a.r + b.r;
    } else {
        ret.r = b.r;
    }
    ret.s = max(max(ret.l, ret.r), max(a.r + b.l, max(a.s, b.s)));
    return ret;
}

void add(int k, int l, int r, int x){
    if (l == r){
        t[k].s = t[k].l = t[k].r = 1;
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) add(k*2, l, mid, x);
    else add(k*2+1, mid+1, r, x);
    t[k] = update(t[k*2], t[k*2+1]);
}

sta get(int k, int l, int r, int x, int y){
    if (l == x && r == y){
        return t[k];
    }
    int mid = (l + r) / 2;
    if (y <= mid) return get(k*2, l, mid, x, y);
    else if (x > mid) return get(k*2+1, mid+1, r, x, y);
    else return update(get(k*2, l, mid, x, mid), get(k*2+1, mid+1, r, mid+1, y));
}

void bld(int k, int l, int r){
    if (l == r){
        t[k].s = t[k].l = t[k].r = 0;
        t[k].len = 1;
        return;
    }
    int mid = (l + r) / 2;
    bld(k*2, l, mid);
    bld(k*2+1, mid+1, r);
    t[k] = update(t[k*2], t[k*2+1]);
}

int ok(){
    for (int i = 1; i <= m; ++ i){
        if (l[i] < r[i]) return 0;
    }
    return 1;
}

void solve(){
    for (int i = 1; i <= nh; ++ i){
        act[i].clear();
        id[i].clear();
    }
    for (int i = 1; i <= n; ++ i){
        act[h[i]].push_back(1);
        id[h[i]].push_back(i);
    }
    for (int i = 1; i <= m; ++ i){
        act[mid[i]].push_back(0);
        id[mid[i]].push_back(i);
    }
    bld(1, 1, n);
    for (int i = nh; i >= 1; -- i){
        for (int j = 0; j < act[i].size(); ++ j){
            if (act[i][j]){
                add(1, 1, n, id[i][j]);
            } else {
                ret[id[i][j]] = get(1, 1, n, x[id[i][j]], y[id[i][j]]).s >= w[id[i][j]];
            }
        }
    }
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &h[i]);
        hh[i] = h[i];
    }
    sort(hh + 1, hh + n + 1);
    nh = unique(hh + 1, hh + n + 1) - hh - 1;
    for (int i = 1; i <= n; ++ i){
        h[i] = lower_bound(hh + 1, hh + nh + 1, h[i]) - hh;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++ i){
        scanf("%d%d%d", &x[i], &y[i], &w[i]);
        l[i] = 1; r[i] = nh;
    }
    while (!ok()){
        for (int i = 1; i <= m; ++ i){  
            mid[i] = (l[i] + r[i] + 1) / 2;
        }
        solve();
        for (int i = 1; i <= m; ++ i){
            if (ret[i]){
                l[i] = mid[i];
            } else {
                r[i] = mid[i] - 1;
            }
        }
    }
    for (int i = 1; i <= m; ++ i){
        printf("%d\n", hh[l[i]]);
    }
    return 0;
}