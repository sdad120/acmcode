//WA
//这题有毒。。什么破读入。。
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
#define N 1005
vector<int> num;
vector<int> prime[N];
int use[N], have[N], tot;
long long dp[2][666666];

void getNum(vector<string> &s){
	num.clear();
	int n = s.size();
	for (int i = 1; i < n; ++ i){
		s[0] += s[i];
	}
	for (int i = 0; i < 1; ++ i){
		int len = s[i].size();
		int now, st = 0;
		while (st < len){
			now = 0;
			while (st < len && s[i][st] != ' '){
				now *= 10;
				now += s[i][st] - '0';
				st ++;
			}
			st ++;
			if (now) num.push_back(now);
		}
	}
}

void getPrime(int id, int num){
	for (long long i = 2; i * i <= num; ++ i){
		if (num % i == 0){
			prime[id].push_back(i);
			while (num % i == 0){
				num /= i;
			}
		}
	}
	if (num > 1){
		prime[id].push_back(num);
	}
}

int test(long long n, int id){
	if (n % num[id]) return 0;
	n /= num[id];
	for (int i = 0; i < prime[id].size(); ++ i){
		if (n % prime[id][i] == 0){
			return 0;
		}
	}
	return 1;
}

int convert(int num){
	int ret = 0;
	for (int i = 0; i < tot; ++ i){
		if (num % have[i] == 0){
			ret ^= (1 << i);
		}
	}
	return ret;
}

class EllysNumbers{
public:
	long long getSubsets(long long n, vector<string> s){
		getNum(s);
		for (int i = 0; i < num.size(); ++ i){
			getPrime(i, num[i]);
		}

		int m = 0;
		for (int i = 0; i < num.size(); ++ i){
			if (test(n, i)){
				use[m++] = i;
			}
		}
		if (m == 0) return 0;

		tot = 0;
		for (int i = 0; i < m; ++ i){
			int now = use[i];
			for (int j = 0; j < prime[now].size(); ++ j){
				have[tot++] = prime[now][j];
			} 
		}

		sort(have, have + tot);
		tot = unique(have, have + tot) - have;
		long long tmp = n;
		for (int i = 0; i < tot; ++ i){
			while (tmp % have[i] == 0){
				tmp /= have[i];
			}
		}
		if (tmp > 1) return 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < m; ++ i){
			printf("%d %d\n", num[use[i]], convert(num[use[i]]));
		}
		int cur = 0;
		dp[0][0] ++;
		dp[0][convert(num[use[0]])] ++;
		for (int i = 0; i < m - 1; ++ i){
			cur ^= 1;
			for (int j = 0; j < (1 << tot); ++ j){
				dp[cur][j] = 0;
			}
			int now = convert(num[use[i+1]]);
			for (int j = 0; j < (1 << tot); ++ j){
				dp[cur][j] += dp[cur^1][j];
				if (j & now) continue;
				dp[cur][j^now] += dp[cur^1][j];
			}
		}

		return dp[cur][(1<<tot)-1];
	}
};//ly;

// int main(){
// 	string str;
// 	str = "4 2 5 6 3";
// 	vector<string> cur;
// 	cur.push_back(str);
// 	ly.getSubsets(12, cur);
// 	return 0;
// }
