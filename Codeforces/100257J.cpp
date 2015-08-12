/*
CF-8-11 Something
*/
#include <cstdio>
#include <map>
using namespace std;
const int mo = 1e9 + 7;
int n, m;
int state[21], id[105], state_num;
int go[21][1<<6];
map<int, int> dp[505], has[1<<21];

inline void inc(int &a, int b){
    a += b;
    if (a >= mo) a -= mo;
}

void dfs(int from, int obs, int x, int to){
    if (x >= m){
        if (id[to] != -1)
            go[id[from]][obs] |= (1 << id[to]);
        return;
    }
    if ((1 << x) & obs){
        dfs(from, obs, x + 1, to);
    } else {
        if (x + 1 < m && ((1 << (x + 1)) & obs) == 0 && ((1 << (x + 1)) & from) == 0 && ((1 << x) & from) == 0){
            dfs(from, obs, x + 2, to);
        }
        if ((1 << x) & from){
            dfs(from, obs, x + 1, to);
        } else {
            dfs(from, obs, x + 1, to + (1 << x));
        }
    }
}

int main(){
    scanf("%d%d", &m, &n);
    for (int i = 0; i < (1 << m); ++ i){
        int flag = 1;
        for (int j = 0; j < m - 1; ++ j){
            if ((i & (1 << j)) > 0 && (i & (1 << (j+1))) > 0){
                flag = 0; break;
            }
        }
        id[i] = -1;
        if (flag){
            state[state_num++] = i;
            id[i] = state_num - 1;
        }
    }

    for (int from = 0; from < state_num; ++ from){
        for (int obs = 0; obs < (1 << m); ++ obs){
            if (state[from] & obs) continue;
            dfs(state[from], obs, 0, 0);
        }
    }

    dp[0][1<<id[0]] = 1;
    for (int i = 0; i < n; ++ i){
        for (map<int, int>::iterator it = dp[i].begin(); it != dp[i].end(); ++ it){
            int from = (*it).first;
            for (int obs = 0; obs < (1 << m); ++ obs){
                int to = 0;
                if (has[from].count(obs) == 0){
                    for (int k = 0; k < state_num; ++ k){
                        if (from & (1 << k)){
                            to |= go[k][obs];
                        }
                    }
                    has[from][obs] = to;
                } else {
                    to = has[from][obs];
                }
                if (to == 0) continue;
                inc(dp[i+1][to], dp[i][from]);
                //printf("%d %d %d %d %d\n", i, from, obs, to, dp[i+1][to]);
            }
        }
    }
    int ans = 0;
    for (map<int, int>::iterator it = dp[n].begin(); it != dp[n].end(); ++ it){
        if ((*it).first & (1 << id[0])){
            //printf("%d %d\n", (*it).first, (*it).second);
            inc(ans, (*it).second);
        }
    }
    printf("%d\n", ans);
    return 0;
}