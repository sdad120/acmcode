struct acAutomation{
	int tr[N][SIZ], fail[N], val[N];
	int node;

	int newNode(){
		memset(tr[node], 0, sizeof(tr[node]));
		fail[node] = val[node] = 0;
		return node++;
	}

	void init() {
		node = 0;
		newNode();
	}

	void insert(char *s, int id) {
		int pos = 0, x, now = 0;
		while (s[pos]) {
			x = s[pos++] - 'a';
			if (!tr[now][x]) {
				tr[now][x] = newNode();
			}
			now = tr[now][x];
		}
		/*
			do some record here
		*/
	}

	void getFail() { //这个版本是已经将tr自动连向失配后的下一个可能节点，与Trie已经不同
		int x, y;
		queue<int> q;
		for (int i = 0; i < SIZ; ++ i){
			x = tr[0][i];
			if (x) {
				fail[x] = 0;
				q.push(x);
			}
		}

		while (!q.empty()) {
			x = q.front(); q.pop();
			for (int i = 0; i < SIZ; ++ i){
				/*
					v = fail[x];
					while (v && !tr[v][i]) v = fail[v];
					fail[y] = tr[v][i];
				*/
				if (!tr[x][i]) {
					tr[x][i] = tr[fail[x]][i];
					continue;
				}
				y = tr[x][i];
				q.push(y);
				fail[y] = tr[fail[x]][i];
				/*
					有时候需要last[]后缀链接数组，表示该点沿着失配指针往回走的第一个有效节点（显然不包括自己）
				*/
			}
		}
	}
}ly;

