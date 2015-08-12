/*
CF-8-11 Something
*/
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
int n, m;
char a[11][44];
int b[11];
ll sta[11];
vector<ll> s;

void dfs(int k, int now, ll sta){
    if (now == b[0]){
        s.push_back(sta);
        return;
    }
    if (k >= n){
        return;
    }
    for (int i = k; i < n; ++ i){
        dfs(i + 1, now + 1, sta ^ (1ll << i));
    }
}

int main(){
   //freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i){
        scanf("%s%d", a[i], &b[i]);
        for (int j = 0; j < n; ++ j){
            if (a[i][j] - '0'){
                sta[i] ^= (1ll << j);
            }
        }
    }
    dfs(0, 0, sta[0]);
    int ans = 0;
    for (int i = 0; i < s.size(); ++ i){
        int flag = 1;
        for (int j = 1; j < m; ++ j){
            ll rem = (s[i] ^ sta[j]);
            int tmp = b[j];
            while (rem){
                rem &= (rem - 1);
                tmp --;
            }
            if (tmp != 0){
                flag = 0;
                break;
            }
        }
        ans += flag;
    }
    printf("%d\n", ans);
    return 0;
}