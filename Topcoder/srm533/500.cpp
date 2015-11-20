#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
int d[105], vis[105];
vector<int> e[105];

void dfs(int k){
	vis[k] = 1;
	for (int i = 0; i < e[k].size(); ++ i){
		int u = e[k][i];
		if (!vis[u]){
			dfs(u);
		}
	}
}

class MagicBoard{
public:
	string ableToUnlock(vector<string> b){
		int n = b.size();
		int m = b[0].size();
		for (int i = 0; i < n + m; ++ i){
			e[i].clear();
			d[i] = vis[i] = 0;
		}
		for (int i = 0; i < n; ++ i){
			for (int j = 0; j < m; ++ j){
				if (b[i][j] == '#'){
					d[i] ++;
					d[j+n] ++;
					e[i].push_back(j+n);
					e[j+n].push_back(i);
				}
			}
		}	
		for (int i = 0; i < n; ++ i){
			if (d[i]){
				dfs(i);
				break;
			}
		}
		int cnt = 0, flag = 1;
		for (int i = 0; i < n + m; ++ i){
			cnt += d[i] & 1;
			if (!vis[i] && d[i]) flag = 0;
		}
		if (cnt > 2) flag = 0;
		cnt = 0;
		for (int i = 0; i < n; ++ i){
			cnt += d[i] & 1;
		}
		if (cnt > 1) flag = 0;
		return flag ? "YES" : "NO";
	}
}ly;

int main(){
	freopen("in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	vector<string> data;
	string str;
	char ch[55];
	for (int i = 0; i < n; ++ i){
		scanf("%s", ch);
		str = "";
		for (int j = 0; j < m; ++ j){
			str += ch[j];
		}
		data.push_back(str);
	}
	cout << ly.ableToUnlock(data) << endl;
	return 0;
}