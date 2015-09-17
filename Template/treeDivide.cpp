struct tree{
	int n, s[N], maxVer[N], p[N];
	vector<int> e[N];

	void init(int _n){
		n = _n;
		for (int i = 0; i < n; ++ i){
			p[i] = 0;
			e[i].clear();
		}
	}

	void centerDfs1(int k, int fa){
		s[k] = 1;
		for (int i = 0; i < e[k].size(); ++ i){
			int u = e[k][i];
			if (p[u] || fa == u) continue;
			centerDfs1(u, k);
			s[k] += s[u];
		}
	}

	void centerDfs2(int k, int fa, int sum, int &ans){
		maxVer[k] = sum - s[k];
		for (int i = 0; i < e[k].size(); ++ i){
			int u = e[k][i];
			if (p[u] || u == fa) continue;
			centerDfs2(u, k, sum, ans);
			maxVer[k] = max(maxVer[k], s[u]);
		}
		if (ans == -1 || maxVer[k] < maxVer[ans]){
			ans = k;
		}
	}

	int getCenter(int k){
		centerDfs1(k, k);
		int ans = -1;
		centerDfs2(k, -1, s[k], ans);
		return ans;
	}

	void treeDivide(int k){
		int root = getCenter(k);
		p[root] = 1;
		for (int i = 0; i < e[root].size(); ++ i){
			int u = e[root][i];
			if (p[u]) continue;
			treeDivide(u);
		}
		/*
			do something here
		*/
		p[root] = 0;
	}
};
