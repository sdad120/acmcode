/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
int n;
#define N 100005
int e[N], in[N], vis[N], instack[N];
stack<int> q;
vector< pair<int, int> > com;
int ret;

void dfs(int k){
    vis[k] = 1;
    instack[k] = 1;
    q.push(k);
    if (vis[e[k]] == 0){
        dfs(e[k]);
    } else
    if (instack[e[k]]){
        ret = k;
    }
    q.pop();
    instack[k] = 0;
}

int main(){
  //  freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &e[i]);
        in[e[i]] ++;
    }
    for (int i = 1; i <= n; ++ i){
        if (in[i] == 0){
            dfs(i);
            if (in[i] == 0){
                com.push_back(make_pair(i, ret));
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        if (vis[i] == 0){
            dfs(i);
            com.push_back(make_pair(i, i));
        }
    }
    if (com[0].first == com[0].second && com.size() == 1){
        puts("0");
        return 0;
    }
    printf("%d\n", (int)com.size());
    for (int i = 0; i < com.size(); ++ i){
        printf("%d %d\n", com[i].second, com[(i+1)%com.size()].first);
    }
    return 0;
}
