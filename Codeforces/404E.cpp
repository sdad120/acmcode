/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
char a[1000005];
int n, ans, h[1000005], p[1000005];
vector<int> zero;
#define LIMIT 0

void get(){
    zero.clear();
    memset(p, 0, sizeof(p));
    int now = 0;
    zero.push_back(0);
    for (int i = 0; i < n; ++ i){
        if (a[i] == 'R'){
            if (now == LIMIT){
                zero.push_back(i);
            } else {
                now ++;
            }
        } else {
            now --;
        }
        h[i] = now;
        //printf("%d %d\n", i, now);
    }
    zero.push_back(n - 1);
    int last = now, start = 0;
    for (int i = 0; i < zero.size() - 1; ++ i){
        for (int j = zero[i]; j < zero[i+1]; ++ j){
            if (h[j] >= last){
                p[i+h[j]-last] = 1;
            }
            if (h[j] == last){
                start = i + 1;
            }
        }
    }
    for (int i = start; i < zero.size() - 1; ++ i){
        if (last + i == 0) continue;
        if (p[i] == 0) ans ++;
    }
    return;
}

int main(){
 //   freopen("in", "r", stdin);
    scanf("%s", a);
    n = strlen(a);
    int now = 0;
    for (int i = 0; i < n; ++ i){
        now += (a[i] == 'R') ? 1 : -1;
    }
    int last = now, flag = 1; now = 0;
    for (int i = 0; i < n - 1; ++ i){
        now += (a[i] == 'R') ? 1 : -1;
        if (now == last){
            flag = 0;
            break;
        }
    }
    if (last == 0){ flag = 0; }
    if (flag){
        puts("1");
        return 0;
    }

    get();
    for (int i = 0; i < n; ++ i){
        if (a[i] == 'R') a[i] = 'L'; else a[i] = 'R';
    }
    get();

    printf("%d\n", ans);
    return 0;
}
