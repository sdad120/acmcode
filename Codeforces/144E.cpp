/*
CF-8-2 Something
*/
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
int n, m;
#define N 100005
pair<int, int> p[N], q[N];
int have[N], id[N];
set< pair<int, int> > choose;

int cmp(int x, int y){
    return p[x] < p[y];
}

int main(){
   // freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 0; i < m; ++ i){
        scanf("%d%d", &x, &y);
        p[i] = make_pair(n-x+1, y);
        id[i] = i;
    }
    sort(id, id + m, cmp);
    int ans = 0, now = 0;
    choose.clear();
    for (int i = 1; i <= n; ++ i){
        while (!choose.empty() && (*choose.begin()).first < i){
            choose.erase(choose.begin());
        }
        while (now < m && p[id[now]].first <= i){
            choose.insert(make_pair(p[id[now]].second, id[now]));
            now ++;
        }
        if (!choose.empty()){
            ans ++;
            pair<int, int> my_choose = (*choose.begin());
            choose.erase(my_choose);
            have[my_choose.second] = 1;
        }
    }
    printf("%d\n", ans);
    for (int i = 0; i < m; ++ i){
        if (have[i]) printf("%d ", i + 1);
    }
    puts("");
    return 0;
}
