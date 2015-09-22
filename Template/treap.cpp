//当区间问题时，利用merge默认a中元素比b中小即可
struct Node{
    int value, size;
    Node *l, *r;
    Node(int _val, int _size, Node*_l, Node*_r){
        value = _val; size = _size; l = _l; r = _r;
    }
    Node(){}
    Node* update() {
		/*
			do some update here	
		*/
        size = l->size + 1 + r->size;
        return this;
    }
};

struct Treap{
    Node bar[N * 15], *foo, *root[N*2], *null;

    void init(int n) { //这是针对n个root的initial
        foo = null = bar;
        null->l = null->r = null;
        foo++;
		for (int i = 0; i <= n; ++ i){
			root[i] = null;
		}
    }

    Node* New_Node(int x) {
        return new(foo++) Node(x, 1, null, null);
    }

    bool gen(int a, int b) {
        return rand() % (a + b) < a;
    }

    Node* merge(Node *a, Node *b) { //合并a和b两个Treap，a中所有元素都比b中小
        if (a == null) return b;
        if (b == null) return a;
        if (gen(a->size, b->size)) {
            a->r = merge(a->r, b);
            return a->update();
        }
        else {
            b->l = merge(a, b->l);
            return b->update();
        }
    }   

    #define PNN pair<Node*, Node*>

    PNN split(Node *u, int s) { //将Treapu的前s个数和其余的数分成两个子树
        if (u == null) return make_pair(null, null);
        Node *l = u->l, *r = u->r;
        if (l->size >= s) {
            PNN res = split(l, s);
            u->l = res.second;
            return make_pair(res.first, u->update());
        }
        else {
            PNN res = split(r, s - (l->size + 1));
            u->r = res.first;
            return make_pair(u->update(), res.second);
        }
    }

    void show(Node *u) {
        if (u == null) return;
        else {
            show(u->l);
            printf("value: %d\n", u->value);
            show(u->r);
        }
    }

    int kth(Node *u, int k) { //给出Treapu里的kth
        if (u == null) return 0;
        if (u->l->size == k -1){
            return u->value;
        } else
        if (u->l->size >= k){
            return kth(u->l, k);
        } else {
            return kth(u->r, k-u->l->size-1);
        }
    }

    int find(Node *u, int x) { //给出Treapu里小于等于x的数的个数
        if (u == null) return 0;
        if (u->value <= x) {
            return u->l->size + 1 + find(u->r, x);
        }
        else return find(u->l, x);
    }

    void erase(Node *&u, int s) { //从Treapu中删除数s
        int tmp = find(u, s);
        PNN res = split(u, tmp - 1);
        PNN ans = split(res.second, 1);
        u = merge(res.first, ans.second);
    }

    void insert(Node *&u, Node *a) { //将一个点插入到Treapu里
        int ans = find(u, a->value);
        PNN res = split(u, ans);
        u = a;
        u = merge(res.first, u);
        u = merge(u, res.second);
    }

    void insert(Node *&u, int s){ //将数s插入到Treapu里
        Node *now = New_Node(s);
        insert(u, now);
    }

    void dfs(Node *a, Node *&b) {
        if (a == null) return ;
        else {
            dfs(a->l, b);
            dfs(a->r, b);
            a->l = a->r = null;
            insert(b, a->update());
        }
    }

    Node* combine(Node *a, Node *b) { //将a和b两个Treap合并，返回新Treap的根 (启发式)
        if (a->size > b->size) {
            swap(a, b);
        }
        dfs(a, b);
        return b;
    }
}ly;
