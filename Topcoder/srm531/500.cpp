#include <cstdio>
#include <cstring>
#include <vector>
#include  <string>
using namespace std;
const int mo = 1e9 + 7;
int f[55][55], d[55][55], du[55], num[55], nxt[55];

class MonsterFarm{
public:
	int numMonsters(vector<string> t){
		int n = t.size();
		for (int i = 0; i < n; ++ i){
			du[i] = num[i] = 0;
			for (int j = 0; j < n; ++ j){
				f[i][j] = d[i][j] = 0;
			}
		}
		for (int i = 0; i < n; ++ i){
			int st = 0;
			while (st < t[i].size()){
				int now = 0;
				while (st < t[i].size() && t[i][st] != ' '){
					now *= 10;
					now += t[i][st] - '0';
					st ++;
				}
				st ++;
				now --;
				d[i][now] = 1;
				f[i][now] ++;
				du[i] ++;
			}
		}

		puts("ok");

		for (int k = 0; k < n; ++ k){
			for (int i = 0; i < n; ++ i){
				for (int j = 0; j < n; ++ j){
					d[i][j] |= (d[i][k] & d[k][j]);
				}
			}

		}

		for (int i = 0; i < n; ++ i){
			if (du[i] > 1 && d[i][i] && d[0][i]){
				return -1;
			}
		}

		num[0] = 1;

		for (int step = 0; step < n + 1; ++ step){
			for (int i = 0; i < n; ++ i){
				nxt[i] = 0;
			}
			for (int i = 0; i < n; ++ i){
				for (int j = 0; j < n; ++ j){
					nxt[j] = (nxt[j] + 1ll * num[i] * f[i][j] % mo) % mo;
				}
			}
			for (int i = 0; i < n; ++ i){
				num[i] = nxt[i];
				printf("%d ", num[i]);
			}
			puts("");
		}

		int ans = 0;
		for (int i = 0; i < n; ++ i){
			ans = (ans + num[i]) % mo;
		}
		return ans;
	}

};
