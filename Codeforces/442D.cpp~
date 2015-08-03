/*
CF-8-2 Something
*/
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 1000005
int n;
int p[N], child[N], dp[N];
pair<int, int> have[N];

void sp(pair<int,int> &now){
    swap(now.first, now.second);
}

int main(){
    //freopen("in", "r", stdin);
    scanf("%d", &n);
    have[1] = make_pair(-1, -1);
    int ans = 0;
    for (int i = 2; i <= n + 1; ++ i){
        scanf("%d", &p[i]);
        dp[i] = 0;
        have[i] = make_pair(-1, -1);
        int now = i;
        while (now != 1){
            int fa = p[now];
            if (have[fa].first == -1){
                have[fa].first = dp[now];
            } else 
            if (have[fa].second == -1 || have[fa].second < dp[now]){
                have[fa].second = dp[now];
                if (have[fa].first < dp[now]){
                    sp(have[fa]);
                }
            }
            if (have[fa].second + 1 > dp[fa]){
                dp[fa] = have[fa].second + 1;
            } else {
                break;
            }
            now = fa;
        }
        printf("%d ", have[1].first + 1);
    }
    puts("");
    return 0;
}
