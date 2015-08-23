struct iSap{
    #define inf 168430090
    int n, st, en, tot;
    int b[M], e[M], c[M], pre[M];
    int cnt[N], cur[N], h[N], d[N];
    queue<int> q;

    void init(int _n, int _st, int _en){
        memset(h, 0, sizeof(h));
        tot = 1; 
        st = _st; en = _en;
        n = _n;
    }

    void bfs(){
        while (!q.empty()) q.pop();
        memset(d, 10, sizeof(d));
        d[en] = 0;
        q.push(en);
        while (!q.empty()){
            int k = q.front(); q.pop();
            for (int go = h[k]; go; go = e[go])
            if (c[go] == 0 && d[b[go]] > d[k] + 1){
                d[b[go]] = d[k] + 1;
                q.push(b[go]);
            }
        }
    }

    void add(int x, int y, int z){
        b[++tot] = y; c[tot] = z; e[tot] = h[x]; h[x] = tot;
        b[++tot] = x; c[tot] = 0; e[tot] = h[y]; h[y] = tot;
    }

    int push_flow(){
        int x = en, flow = inf;
        while (x != st){
            flow = min(flow,c[pre[x]]);
            x = b[pre[x] ^ 1];
        }
        x = en;
        while (x != st){
            c[pre[x]] -= flow;
            c[pre[x] ^ 1] += flow;
            x = b[pre[x] ^ 1];
        }
        return flow;
    }                   

    int max_flow(){
        bfs();
        //memset(d,0,sizeof(d));
        memset(cnt,0,sizeof(cnt));
        for (int i = 0; i < n; ++ i){
            if (d[i] != inf) cnt[d[i]]++;
        }
        int x = st, ans = 0;
        memset(cur, 0, sizeof(cur));
        for (int i = 0; i < n; ++ i){
            cur[i] = h[i];
        }
        while (d[st] < n){
            if (x == en){
                ans += push_flow();
                x = st;
            }   
            int ok = 0;
            for (int go = cur[x]; go; go = e[go]){
                if (c[go] && d[x] == d[b[go]] + 1){
                    ok = 1;
                    pre[b[go]] = go;
                    cur[x] = go;
                    x = b[go];
                    break;
                }
            }
            if (!ok){
                int tmp = n - 1;
                for (int go = h[x]; go; go = e[go]){
                    if (c[go]){
                        tmp = min(tmp, d[b[go]]);
                    }
                }
                if (-- cnt[d[x]] == 0) break;
                d[x] = tmp + 1;
                cnt[d[x]] ++;
                cur[x] = h[x];
                if (x != st) x = b[pre[x] ^ 1];
            }
        }
        return ans;
    }
};
