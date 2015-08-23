struct minCost{
    #define inf 168430090
    int n, st, en, tot;
    int b[M], c[M], w[M], e[M];
    int h[N], pre[N], p[N], d[N];
    queue<int> q;

    void init(int _n,int _st,int _en){
        memset(h, 0, sizeof(h));
        tot = 1;
        st = _st; en = _en;
        n = _n;
    }

    void add(int x,int y,int z,int cost){
        b[++tot] = y; c[tot] = z; w[tot] = cost; e[tot] = h[x]; h[x] = tot;
        b[++tot] = x; c[tot] = 0; w[tot] = -cost; e[tot] = h[y]; h[y] = tot;
    }

    int push_flow(){
        int x = en, flow = inf;
        while (x != st){
            flow = min(flow, c[pre[x]]);
            x = b[pre[x] ^ 1];
        }
        x = en;
        while (x != st){
            c[pre[x]] -= flow; c[pre[x]^1] += flow;
            x = b[pre[x] ^ 1];
        }
        return flow * d[en];
    }

    int spfa(){
        memset(d, 10, sizeof(d));
        memset(p, 0, sizeof(p));
        q.push(st); p[st] = 1; d[st] = 0;
        while (!q.empty()){
            int x = q.front(); q.pop();
            p[x] = 0;
            for (int go = h[x]; go; go = e[go])
                if (c[go] && d[b[go]] > d[x] + w[go]){
                    d[b[go]] = d[x] + w[go];
                    pre[b[go]] = go;
                    if (p[b[go]] == 0){
                        p[b[go]] = 1;
                        q.push(b[go]);
                    }
                }
        }
        return d[en] < inf;
    }

    int min_cost(){
        int ans = 0;
        while (spfa()) ans += push_flow();
        return ans;
    }
};
