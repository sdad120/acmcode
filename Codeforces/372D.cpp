/*
CF-8-11 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
using namespace std;
int n, k;
#define N 100005
int f[N][20], p[N], t[N], dep[N], cnt;
vector<int> e[N];
set<int> id;

void dfs(int k){
    p[k] = ++ cnt;
    t[cnt] = k;
    for (int i = 0; i < e[k].size(); ++ i){
        int u = e[k][i];
        if (u == f[k][0]) continue;
        dep[u] = dep[k] + 1;
        f[u][0] = k;
        for (int i = 1; i < 18; ++ i){
            f[u][i] = f[f[u][i-1]][i-1];
        }
        dfs(u);
    }
}

int get(int _x, int _y){
    int x = _x, y = _y;
    if (dep[x] < dep[y]) swap(x, y);
    while (dep[x] != dep[y]){
        for (int i = 17; i >= 0; -- i){
            if (dep[x] - (1 << i) >= dep[y]){
                x = f[x][i];
            }
        }
    }
    while (f[x][0] != f[y][0]){
        for (int i = 17; i >= 0; -- i){
            if (f[x][i] != f[y][i]){
                x = f[x][i];
                y = f[y][i];
                break;
            }
        }
    }
    int lca = (x == y) ? x : f[x][0];
    return dep[_x] + dep[_y] - 2 * dep[lca]; 
}

int get(int k){
    set<int>::iterator left, right;
    right = id.lower_bound(p[k]);
    if (right == id.end()){
        left = -- right;
        right = id.begin();
    } else
    if (right == id.begin()){
        left = --id.end();
    } else {
        left = right; -- left;
    }
    return (get(t[*left], k) + get(t[*right], k) - get(t[*left], t[*right])) / 2;
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d", &n, &k);
    int x, y;
    for (int i = 1; i < n; ++ i){
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }    
    dfs(1);
    int l = 1, r = 1, size = 1, ans = 0;
    id.insert(p[1]);
    while (l <= n){
        while (r < n && size + get(r + 1) <= k){
            size += get(++r);
            id.insert(p[r]);
        }
        ans = max(ans, r - l + 1);
        if (l == r){
            size += get(++r);
            id.insert(p[r]);
        }
        id.erase(p[l]);
        size -= get(l++);
    }
    printf("%d\n", ans);
    return 0;
}