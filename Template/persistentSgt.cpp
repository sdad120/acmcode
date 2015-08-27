//CF276E
//需要留一个p[0]作为空结点，以及需要注意空结点在update和get中的出现
//0-inf做为区间的动态开点线段树写法相同

struct Node{
    int l, r, t, L, R, len;
    Node(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0) : l(a), r(b), t(c), L(d), R(e), len(f) {}
}p[N * 20];

struct Sgt{
    int root[N], node, n;

    void init(int _n){
        node = 1;
        n = _n;
    }

    int New_Node() {
        p[node] = Node();
        return node++;
    }

    Node ret;

    Node update(const Node&Z, const Node&X, const Node&Y, int l, int r, int mid){
        ret = Node();
        ret.l = Z.l; ret.r = Z.r;
        ret.len = r - l + 1;
        if (X.L == mid - l + 1){
            ret.L = X.L + Y.L;
        } else {
            ret.L = X.L;
        }

        if (Y.R == r - mid){
            ret.R = Y.R + X.R;
        } else {
            ret.R = Y.R;
        }

        ret.t = max(X.t, Y.t);
        ret.t = max(ret.t, max(ret.L, ret.R));
        ret.t = max(ret.t, X.R + Y.L);

        return ret;
    }

    void add(int pre, int &now, int l, int r, int x){
        now = New_Node();
        if (l == r){
            p[now].L = p[now].R = p[now].t = p[now].len = 1;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid){
            add(p[pre].l, p[now].l, l, mid, x);
            p[now].r = p[pre].r;
        } else {
            add(p[pre].r, p[now].r, mid+1, r, x);
            p[now].l = p[pre].l;
        }
        p[now] = update(p[now], p[p[now].l], p[p[now].r], l, r, mid);
    }

    Node get(int now, int l, int r, int x, int y){
        if (now == 0){
            return Node();
        }
        if (l == x && r == y){
            return p[now];
        }
        int mid = (l + r) / 2;
        if (y <= mid) return get(p[now].l, l, mid, x, y);
        else if (x > mid) return get(p[now].r, mid+1, r, x, y);
        else return update(ret, get(p[now].l, l, mid, x, mid), get(p[now].r, mid+1, r, mid+1, y), x, y, mid);
    }

}ly;
