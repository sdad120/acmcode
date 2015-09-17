#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
using namespace std;
int G[105], F[105][205], S[105][205];
int dp[105][205][205], gaoDp[105][205], fuckDp[105][205];
int vis[105][205][205], visGao[105][205], visFuck[105][205];
int mo;
const int ZERO = 101;

int ok(int x){
    return x >= 0 && x <= 2 * ZERO;
}

int fuck(int, int);
int gao(int, int);
int solve(int, int, int);

int fuck(int n, int st){
    if (!ok(st)) return 0;
    if (visFuck[n][st]) return fuckDp[n][st];
    visFuck[n][st] = 1;
    if (n == 0){
        if (st == ZERO){
            fuckDp[n][st] = 1;
        } else {
            fuckDp[n][st] = 0;
        }
        return fuckDp[n][st];
    }
    int &ret = fuckDp[n][st];
    ret = (ret + fuck(n - 1, st + 1)) % mo;
    ret = (ret + fuck(n - 1, st - 1)) % mo;
    for (int j = 2; j <= n; ++ j){
        if (st == ZERO){
            ret = (ret + 1ll * G[j-2] * fuck(n - j, ZERO)) % mo;
        } else {
            ret = (ret + 1ll * gao(j - 2, st) * fuck(n - j, ZERO)) % mo;
        }
    }
    return ret;
}

int gao(int n, int st){
    if (!ok(st)) return 0;
    if (visGao[n][st]) return gaoDp[n][st];
    visGao[n][st] = 1;
    if (n == 0){
        if (st == ZERO){
            gaoDp[n][st] = 1;
        } else {
            gaoDp[n][st] = 0;
        }
        return gaoDp[n][st];
    }
    int &ret = gaoDp[n][st];
    ret = (ret + F[n][2*ZERO-st] + fuck(n, st)) % mo;
    return ret;
}

int solve(int n, int st, int ed){
    if (!ok(st) || !ok(ed)) return 0;
    if (vis[n][st][ed]) return dp[n][st][ed];
    vis[n][st][ed] = 1;
    if (n == 0){
        if (st == ed){
            dp[n][st][ed] = 1;
        } else {
            dp[n][st][ed] = 0;
        }
        return dp[n][st][ed];
    }
    int &ret = dp[n][st][ed];
    ret = (ret + solve(n - 1, st + 1, ed)) % mo;
    ret = (ret + solve(n - 1, st - 1, ed)) % mo;
    for (int j = 2; j <= n; ++ j){
        if (st == ZERO){
            ret = (ret + 1ll * G[j-2] * solve(n - j, ZERO, ed)) % mo;
        } else {
            ret = (ret + 1ll * gao(j - 2, st) * solve(n - j, ZERO, ed)) % mo;
        }
    }
    return ret;
}

class Brainstuck{
public: 
    int countPrograms(int n, int m){
        mo = m;
        G[0] = 1;
        for (int i = 1; i <= n; ++ i){
            G[i] = G[i-1] * 2 % mo;
            for (int j = 0; j < i - 1; ++ j){
                G[i] = (G[i] + 1ll * G[j] * G[i-j-2]) % mo;
            }
        }
        S[0][ZERO] = 1;
        for (int i = 1; i <= 100; ++ i){
            for (int j = 0; j < 2 * ZERO; ++ j){
                if (j > 0) S[i][j] = (S[i][j] + S[i-1][j-1]) % mo;
                if (j < 2 * ZERO)S[i][j] = (S[i][j] + S[i-1][j+1]) % mo;
            }
            for (int j = 1; j <= 100; ++ j){
                for (int k = j + j; k <= 100; k += j){
                    F[i][k+ZERO] = (F[i][k+ZERO] + S[i][j+ZERO]) % mo;
                    F[i][ZERO-k] = (F[i][ZERO-k] + S[i][ZERO-j]) % mo;
                }
            }
        }
        int ret = 0;
        for (int i = 0; i <= 2 * ZERO; ++ i){
            // int tmp = solve(n, ZERO, i);
            // if (tmp) printf("%d %d\n", i - ZERO, tmp);
            ret = (ret + solve(n, ZERO, i)) % mo;
        }
        return ret;
    }
}ly;

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", ly.countPrograms(n, m));
    return 0;
}