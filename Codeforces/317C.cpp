/*
CF-8-16 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n, v, m;
#define N 305
int a[N], b[N], vis[N], d[N][N], e[N][N];
queue<int> high, low;

struct sta{
    int x, y, z;
    sta(int _x, int _y, int _z){
        x = _x; y = _y; z = _z;
    }
};

void add(int x){
    vis[x] = 1;
    if (a[x] > b[x]){
        high.push(x);
    } 
    if (a[x] < b[x]){
        low.push(x);
    }
    for (int i = 0; i < n; ++ i){
        if (i == x || e[x][i] == 0 || vis[i]) continue;
        add(i);
    }
}

vector<sta> ans;
void print(int x, int y, int det){
    if (x == y) return;
    for (int i = 0; i < n; ++ i){
        if (i == y || e[i][y] == 0 || d[x][i] + d[i][y] != d[x][y]) continue;
        int first = min(det, a[i]);
        if (first) ans.push_back(sta(i, y, first));
        print(x, i, det);
        if (det - first) ans.push_back(sta(i, y, det-first));
        break;
    }
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d%d%d", &n, &v, &m);
    for (int i = 0; i < n; ++ i){
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++ i){
        scanf("%d", &b[i]);
    }
    int x, y;
    memset(d, 10, sizeof(d));
    for (int i = 0; i < n; ++ i){
        d[i][i] = e[i][i] = 0;
    }
    for (int i = 0; i < m; ++ i){
        scanf("%d%d", &x, &y);
        -- x; -- y;
        d[x][y] = d[y][x] = 1;
        e[x][y] = e[y][x] = 1;
    }
    for (int k = 0; k < n; ++ k){
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j < n; ++ j){
                d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
            }
        }
    }
    for (int i = 0; i < n; ++ i){
        if (vis[i]) continue;
        add(i);
        while(!high.empty() && !low.empty()){
            int highv = high.front();
            int lowv = low.front();
            int det = min(a[highv] - b[highv], b[lowv] - a[lowv]);
            print(highv, lowv, det);
            a[highv] -= det;
            a[lowv] += det;
            while (!high.empty() && a[high.front()] == b[high.front()]) high.pop();
            while (!low.empty() && a[low.front()] == b[low.front()]) low.pop(); 
        }
        if (!high.empty() || !low.empty()){
            puts("NO");
            return 0;
        }   
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++ i){
        printf("%d %d %d\n", ans[i].x + 1, ans[i].y + 1, ans[i].z);
    }
    return 0;
}