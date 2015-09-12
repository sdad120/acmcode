#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 300005
ll x[N], y[N], s[N];
int n, id[N];

int cmp(int a, int b){
    return x[a] < x[b];
}

struct Tree{
    ll c[N];
    void add(int x, ll y){
        for (int i = x; i <= n; i += i & -i){
            c[i] += y;
        }
    }
    ll get(int x){
        ll ret = 0;
        for (int i = x; i > 0; i -= i & -i){
            ret += c[i];
        }
        return ret;
    }
}A, B;

class ThreePoints{
public:
    ll countColoring(int _n, int xzero, int xmul, int xadd, int xmod, int yzero, int ymul, int yadd, int ymod){
        n = _n;
        x[0] = xzero;
        y[0] = yzero;
        s[0] = yzero;
        id[0] = 0;
        for(int i = 1; i < n; ++ i){
            x[i] = (x[i-1] * xmul + xadd) % xmod;
            y[i] = (y[i-1] * ymul + yadd) % ymod;
            s[i] = y[i];
            id[i] = i;
        }
        sort(s, s + n);
        sort(id, id + n, cmp);
        for (int i = 1; i <= n; ++ i){
            A.c[i] = B.c[i] = 0;
        }
        ll ret = 0;
        for (int i = n - 1; i >= 0; -- i){
            int k = id[i];
            int ny = lower_bound(s, s + n, y[k]) - s + 1;
            ret -= B.get(n) - B.get(ny);
            int cnt = A.get(n) - A.get(ny);
            ret += 1ll * cnt * (cnt - 1) / 2;
            A.add(ny, 1);
            B.add(ny, cnt);
        }
        return ret;
    }
};