#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int n;
#define N 205
const int mo = 1e4 + 7;
vector<int> e[N];
int dp[2][N][N], f[N], nf[N], s[N], maxCompo[N];

void preDp(int k, int fa, int ty){
	s[k] = 1;
	for (int i = 0; i <= n; ++ i){
		dp[ty][k][i] = 0;
	}
	dp[ty][k][0] = 1;
	for (int i = 0; i < e[k].size(); ++ i){
		int u = e[k][i];
		if (u == fa) continue;
		preDp(u, k, ty);
		for (int a = 0; a <= s[k] + s[u]; ++ a){
			f[a] = 0;
		}
		for (int a = 0; a <= s[u]; ++ a){
			for (int b = s[k]; b >= 0; -- b){
				f[a+b] = (f[a+b] + dp[ty][u][a] * dp[ty][k][b]) % mo;
			}
		}
		s[k] += s[u];
		for (int a = 0; a <= s[k]; ++ a){
			dp[ty][k][a] = f[a];
		}
	}
	for (int a = s[k] - 1; a >= 0; -- a){
		dp[ty][k][a+1] = dp[ty][k][a];
	}
	dp[ty][k][0] = 1;
}

void getCenter(int k, int fa){
	s[k] = 1;
	maxCompo[k] = 0;
	for (int i = 0; i < e[k].size(); ++ i){
		int u = e[k][i];
		if (u == fa) continue;
		getCenter(u, k);
		s[k] += s[u];
		maxCompo[k] = max(maxCompo[k], s[u]);
	}
}

int main(){
	freopen("in", "r", stdin);
	int _, __ = 0;
	scanf("%d", &_);
	while (_--){
		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i){
			e[i].clear();
		}
		for (int i = 0; i < n - 1; ++ i){
			int x, y;
			scanf("%d%d", &x, &y);
			e[x].push_back(y);
			e[y].push_back(x);
		}
		getCenter(1, 0);
		for (int i = 1; i <= n; ++ i){
			maxCompo[i] = max(maxCompo[i], n - s[i]);
		}

		int centerFirst = 0, centerSecond = 0;
		for (int i = 1; i <= n; ++ i){
			if (centerFirst == 0 || maxCompo[centerFirst] > maxCompo[i]){
				centerFirst = i;
				centerSecond = 0;
			} else 
			if (maxCompo[centerFirst] == maxCompo[i]){
				centerSecond = i;
			}
		}
		// printf("%d %d\n", centerFirst, centerSecond);
		int ans = 0;
		if (centerSecond){
			preDp(centerFirst, centerSecond, 0);
			preDp(centerSecond, centerFirst, 1);
			for (int i = 1; i <= n; ++ i){
				ans = (ans + dp[0][centerFirst][i] * dp[1][centerSecond][i]) % mo;
			}
		} else {
			preDp(centerFirst, 0, 0);
			for (int i = 0; i < e[centerFirst].size(); ++ i){
				int maxRoot = e[centerFirst][i];
				for (int i = 0; i <= n; ++ i){
					f[i] = 0;
				}
				f[0] = 1;
				int siz = 0;
				for (int j = 0; j < e[centerFirst].size(); ++ j){
					int u = e[centerFirst][j];
					if (u == maxRoot) continue;
					for (int a = 0; a <= siz + s[u]; ++ a){
						nf[a] = 0;
					}
					for (int a = 0; a <= s[u]; ++ a){
						for (int b = siz; b >= 0; -- b){
							nf[a+b] = (nf[a+b] + f[b] * dp[0][u][a]) % mo;
						}
					}
					siz += s[u];
					for (int a = 0; a <= siz; ++ a){
						f[a] = nf[a];
					}
				}
				for (int i = 1; i <= n; ++ i){
					f[i] = (f[i] + f[i-1]) % mo;
				}
				for (int maxVal = 1; maxVal <= n; ++ maxVal){
					ans = (ans - dp[0][maxRoot][maxVal] * f[maxVal-1]) % mo;
				}
			}
			for (int i = 1; i <= n; ++ i){
				ans = (ans + dp[0][centerFirst][i]) % mo;
			}		
		}
		if (ans < 0) ans += mo;
		printf("Case %d: %d\n", ++ __, ans);
	}
	return 0;
}