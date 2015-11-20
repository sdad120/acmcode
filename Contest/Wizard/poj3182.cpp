#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
int n, m;
char a[55][55];
int sx, sy, px, py;
int dp[55][55][2];
int above[55][55];
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct node{
    int x, y, st;
    node(int _x = 0, int _y = 0, int _st = 0){
        x = _x; y = _y; st = _st;
    }
};

queue<node> q;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i){
        scanf("%s", a[i]);
        for (int j = 0; j < m; ++ j){
            if (a[i][j] == '*'){
                sx = i; sy = j;
            }
            if (a[i][j] == 'X'){
                px = i; py = j;
            }
        }
    }
    for (int i = px; i < n; ++ i){
        above[i][py] = 1;
    }
    memset(dp, 10, sizeof(dp));
    dp[sx][sy][0] = 0;
    q.push(node(sx, sy, 0));
    while (!q.empty()){
        int x = q.front().x, y = q.front().y, st = q.front().st;
        q.pop();
        for (int i = 0; i < 8; ++ i){
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx >= 0 && ty >= 0 && tx < n && ty < m && a[tx][ty] != 'X'){
                int newst = st;
                if (dy[i] > 0){
                    newst ^= above[x][y];
                } else 
                if (dy[i] < 0){
                    newst ^= above[tx][ty];
                }
                if (dp[tx][ty][newst] > dp[x][y][st] + 1){
                    dp[tx][ty][newst] = dp[x][y][st] + 1;
                    q.push(node(tx, ty, newst));
                }
            }
        }
    }
    printf("%d\n", dp[sx][sy][1]);
    return 0;
}
