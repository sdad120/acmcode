#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mo = 1e9 + 7;
int dp[31][31][31][1<<9];
int n, k;

int dfs(int l, int r, int rem, int sta){
	int &res = dp[l][r][rem][sta];
	if (res != -1) return res;
	if (r == n){
		return res = (rem == 0 && sta == 0);
	}
	if (l == r){
		if (sta >> k & 1){
			res = 0;
		} else {
			res = dfs(max(0, r + 1 - k), r + 1, rem, sta << 1);
		}
		return res;
	}
	res = 0;
	if (rem > 0){
		res += dfs(l, r, rem - 1, sta ^ (1 + (1 << (r - l))));
	}
	res += dfs(l + 1, r, rem, sta);
	if (res >= mo) res -= mo;
	return res;
}

class DengklekBuildingRoads{
public:
	int numWays(int N, int M, int K){
		memset(dp, -1, sizeof(dp));
		n = N; k = K;
		return dfs(0, 0, M, 0);
	}
};