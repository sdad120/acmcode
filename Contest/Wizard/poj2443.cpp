#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;
int n, m;
bitset<1005> p[10005], now;

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        int x, y;
        scanf("%d", &x);
        for (int j = 0; j < x; ++ j){
            scanf("%d", &y);
            p[y][i] = 1;
        }
    }
    scanf("%d", &m);
    while (m--){
        int x, y;
        scanf("%d%d", &x, &y);
        now = p[x] & p[y];
        if (now.count() > 0){
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}
