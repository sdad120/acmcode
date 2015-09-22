//CF276E，POJ2104，ZJU2112，HDU4348，HIHOCDER1232
//0-inf做为区间的动态开点线段树写法类似

struct Node{
	int ls, rs, val;
	Node(int a = 0, int b = 0, int c = 0): ls(a), rs(b), val(c){}
}p[N*20];

//区间可持续需要开大空间
//p[0]做为空结点，在update中注意不能造成任何影响
struct SegmentTree{
	int root[N], node, n;

	void init(int _n, int tot){
		node = 1;
		n = _n;
		for (int i = 0; i <= tot; ++ i){
			root[i] = 0;
		}
	}

	int newNode(){
		p[node] = Node();
		return node++;
	}

	//单点更新，每一次add都会进行一次path copy
	void add(int pre, int &now, int l, int r, int x){
		now = newNode();
		if (l == r){
			/*
				do some update from pre here
				ex: p[now].val = p[pre].val + 1;
			*/
			return;
		}
		int mid = (l + r) / 2;
		if (x <= mid){
			add(p[pre].ls, p[now].ls, l, mid, x);
			p[now].rs = p[pre].rs;		
		}		
		else{
			add(p[pre].rs, p[now].rs, mid+1, r, x);
			p[now].ls = p[pre].ls;		
		}		
		/*
			do some update from son here
			ex: p[now].val = p[p[now].ls].val + p[p[now].rs].val;
		*/
	}

	void pushDown(int k, int l, int r){
		if (l != r){
			int nowLson = p[k].ls;
			int nowRson = p[k].rs;
			/* 
				if update then
				nowL(R)son = newNode(); p[nowL(R)son] = p[p[k].l(r)s];
				do some update from tag			
			*/
			p[k].ls = nowLson;
			p[k].rs = nowRson;
			p[k].tag = 0;
		}
	}

	//区间更新
	void add(int pre, int &now, int l, int r, int x, int y, int z){
		pushDown(pre, l, r);
		now = newNode();
		if (x <= l && r <= y){
			/*
				do some update from pre here
			*/
			return;
		}
		int mid = (l + r) / 2;
		if (x <= mid) add(p[pre].ls, p[now].ls, l, mid, x, y, z);
		if (y > mid) add(p[pre].rs, p[now].rs, mid + 1, r, x, y, z);
		if (p[now].ls == 0) p[now].ls = p[pre].ls;
		if (p[now].rs == 0) p[now].rs = p[pre].rs;
		/*
			do some update from son here
		*/
	}
};
