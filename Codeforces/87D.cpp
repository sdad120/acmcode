/*
CF-8-2 Something
*/
#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>
#include <vector>
using namespace std;
int n;
#define N 200005
int x[N], y[N], z[N], id[N];
int f[N], s[N], size[N], tot_size;
long long ans[N], now;
vector< pair<int, int> > edge[N];

int getf(int x){
	return f[x] == x ? x : f[x] = getf(f[x]);
}

int cmp(int x, int y){
	return z[x] < z[y];
}

void dfs(int k, int fa){
	size[k] = s[k];
	for (int i = 0; i < edge[k].size(); ++ i){
		int u = edge[k][i].first;
		if (u != fa){
			dfs(u, k);
			size[k] += size[u];
		}
	}
}

void dfs2(int k, int fa){
	for (int i = 0; i < edge[k].size(); ++ i){
		int u = edge[k][i].first;
		if (u != fa){
			dfs2(u, k);
			//printf("%d\n", edge[k][i].second);
			ans[edge[k][i].second] = 2ll * size[u] * (tot_size - size[u]);
		}
	}
}

int main(){
	// freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i < n; ++ i){
		scanf("%d%d%d", &x[i], &y[i], &z[i]);
		id[i] = i;
	}
	sort(id + 1, id + n, cmp);
	for (int i = 1; i <= n; ++ i){
		f[i] = i;
		s[i] = 1;
	}
	int L = 1;
	for (int i = 1; i <= n - 1; ++ i){
		if (i != n - 1 && z[id[i]] == z[id[i+1]]) continue;
		for (int j = L; j <= i; ++ j){
			int k = id[j];
			int tx = getf(x[k]), ty = getf(y[k]);
			edge[tx].clear();
			edge[ty].clear();
		}
		for (int j = L; j <= i; ++ j){
			int k = id[j];
			int tx = getf(x[k]), ty = getf(y[k]);
			edge[tx].push_back(make_pair(ty, k));
			edge[ty].push_back(make_pair(tx, k));
		}
		for (int j = L; j <= i; ++ j){
			int root = getf(x[id[j]]);
			if (ans[edge[root][0].second]) continue;
			dfs(root, 0);
			tot_size = size[root];
			dfs2(root, 0);
		}
		for (int j = L; j <= i; ++ j){
			int k = id[j];
			int tx = getf(x[k]), ty = getf(y[k]);
			f[tx] = ty;
			s[ty] += s[tx];
		}
		L = i + 1;
	}
	long long now = 0;
	for (int i = 1; i < n; ++ i){
		now = max(now, ans[i]);
	}
	int cnt = 0;
	for (int i = 1; i < n; ++ i){
		if (ans[i] == now) cnt ++;
	}
	cout << now << " " << cnt << endl;
	for (int i = 1; i < n; ++ i){
		if (ans[i] == now) printf("%d ", i);
	}
	return 0;
}
