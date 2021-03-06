/*
CF-8-16 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
int n, m;
struct sta{
    int r, p;
    bool operator < (const sta&x)const{
        return x.r < r;
    }
};
#define N 200005
priority_queue<sta> q;
vector<sta> a[N];
int b[N];

int main(){
 //   freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &b[i]);
    }
    int x;
    sta y;
    long long ans = 0;
    for (int i = 1; i <= m; ++ i){
        scanf("%d%d%d", &x, &y.r, &y.p);
        a[x].push_back(y);
        ans += y.p;
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = 0; j < a[i].size(); ++ j){
            q.push(a[i][j]);
        }
        while (!q.empty() && q.top().r < i){
            q.pop();
        }
        while (!q.empty() && b[i]){
            y = q.top(); q.pop();
            int tmp = min(y.p, b[i]);
            y.p -= tmp; b[i] -= tmp; ans -= tmp;
            if (y.p) q.push(y);
        }
    }
    cout << ans << endl;
    return 0;
}