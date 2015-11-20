struct HeavyLight{
	vector<int> e[N];
	int s[N], d[N], f[N];
	// s -> size , d -> dep , f -> father 
	int h[N], p[N], fp[N];
	// h -> which link this node is belong
	// p -> the no. of this node in sgt
	// fp -> which node this sgt no. is 
	int id;
	// id -> the number of the node now
	// cuz the sgt, id is 1-base

	void init(int _n){
		n = _n;
		for (int i = 0; i < n; ++ i){
			e[i].clear();
		}
		id = 1;
	}

	void dfs1(int k){
	    s[k] = 1;
	    for (int i = 0; i < e[k].size(); ++ i){
	        int u = e[k][i];
	        if (u == f[k]) continue;
	        d[u] = d[k] + 1;
	        f[u] = k;
	        dfs1(u);
	        s[k] += s[u];
	    }
	}

	void dfs2(int k, int o){
	    h[k] = o;
	    p[k] = id;
	    fp[id++] = k;
	    int tmp = -1;
	    for (int i = 0; i < e[k].size(); ++ i){
	        int u = e[k][i];
	        if (u == f[k]) continue;
	        if (tmp == -1 || s[tmp] < s[u]){
	            tmp = u;
	        }
	    }
	    if (tmp == -1) return;
	    dfs2(tmp, o);
	    for (int i = 0; i < e[k].size(); ++ i){
	        int u = e[k][i];
	        if (tmp == u || f[k] == u) continue;
	        dfs2(u, u);
	    }
	}

	void add(int x, int y){
	    int f1 = h[x], f2 = h[y];
	    while (f1 != f2){
	        if (d[f1] < d[f2]){
	            swap(f1, f2);
	            swap(x, y);
	        }
	        /*
	        	p[f1] - p[x] is a part of the link
	        */ 
	        x = f[f1];
	        f1 = h[x];
	    }
	    if (d[x] > d[y]) swap(x, y);
	    /*
			p[x] - p[y] is a part of the link
	    */
	}

	void solve(){
		dfs1();
		dfs2();
	}
}ly;