#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define N 100005
int n, m, q;
map< pair<int, int>, pair<int, int> > ans;
vector<int> e[N];
int d[N];

int main(){
  //  freopen("in", "r", stdin);
    int _, __ = 0;
    scanf("%d", &_);
    while (_--){
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i){
            e[i].clear();
            d[i] = 0;
        }
        for (int i = 1; i <= m; ++ i){
            int x, y;
            scanf("%d%d", &x, &y);
            e[x].push_back(y);
            e[y].push_back(x);
            d[x] ++; d[y] ++;
        }

        for (int i = 1; i <= n; ++ i){
            sort(e[i].begin(), e[i].end());
        }

        ans.clear();
        scanf("%d", &q);
        printf("Case #%d:\n", ++ __);
        while (q--){
            int x, y;
            scanf("%d%d", &x, &y);
            if (d[x] > d[y] || (d[x] == d[y] && x > y)) swap(x, y);
            pair<int, int> out;
            if (ans.count(make_pair(x, y))){
                out = ans[make_pair(x, y)];
            } else 
            if (x == y){
                out.first = 0; out.second = 1;
            } else {
                int cnt = 0;
                cnt = upper_bound(e[x].begin(), e[x].end(), y) - lower_bound(e[x].begin(), e[x].end(), y);
                out.first = 1;
                if (cnt == 0){
                    out.first = 2;
                    for (int i = 0; i < e[x].size(); ++ i){
                        int u = e[x][i];
                        cnt += upper_bound(e[u].begin(), e[u].end(), y) - lower_bound(e[u].begin(), e[u].end(), y);
                    }
                    if (cnt == 0){
                        out.first = 3;
                    }
                }
                out.second = cnt;
            }
            ans[make_pair(x, y)] = out;
            if (out.first <= 2){
                printf("%d %d\n", out.first, out.second);
            } else {
                printf("The pair of cities are not connected or too far away.\n");
            }
        }
    }
    return 0;
}
