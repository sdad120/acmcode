/*
CF-8-16 Something
*/
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int n, t;
#define N 300005
struct point{
    int x, y;
    void input(){
        scanf("%d%d", &x, &y);
    }
}p[N], A;
int next[N], cha[N];
long long sum[N];

long long cross(point a, point b, point c){
    return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (b.y - a.y) * (c.x - a.x);
}

int main(){
 //   freopen("in", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        p[i].input();
    }
    reverse(p, p + n);
    long long area = 0;
    for (int i = 0; i < n; ++ i){
        area += cross(p[0], p[i], p[(i+1)%n]);
        p[n+i] = p[2*n+i] = p[i];
    }
    scanf("%d", &t);
    while (t--){
        A.input();
        long long tmp_area = 0;
        for (int i = 0; i < n; ++ i){
            tmp_area += abs(cross(A, p[i], p[(i+1)%n]));
        }
        if (tmp_area != area){
            puts("0");
            continue;
        }
        int r = 1;
        for (int i = 0; i < 2 * n; ++ i){
            while (cross(p[i], A, p[r+1]) < 0 && (r + 1) % n != i) ++ r;
            cha[i] = r;
        }
        for (int i = 0; i < 3 * n; ++ i){
            sum[i] = (i > 0 ? sum[i-1] : 0) + cha[i];
        }
        long long ans = 0;
        for (int i = 0; i < n; ++ i){
            ans += (sum[cha[i]] - sum[i]) - 1ll * (cha[i] - i) * cha[i];
            ans += 1ll * (i + n - cha[i] - 1) * cha[i+n] - (sum[i+n-1] - sum[cha[i]]);
        }
        ans = ans / 6;
        cout << ans << endl;
    }
    return 0;
}