/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
#define N 100005

struct SA{
    char s[N];
    int sa[N], na[N], r[N], nr[N][2], c[N], h[N], n;

    void bld(){
        memset(c, 0, sizeof(c));
        for (int i = 0; i < n; ++ i){
            c[s[i]] ++;
        }
        for (int i = 0; i < 256; ++ i){
            c[i + 1] += c[i];
        }
        for (int i = 0; i < n; ++ i){
            r[i] = c[s[i]] - 1;
        }
        for (int k = 1; k <= n; k <<= 1){ // n == 1的时候所以特意加了 k < n -> k <= n
            for (int i = 0; i < n; ++ i){
                nr[i][0] = r[i];
                nr[i][1] = i + k < n ? r[i + k] + 1 : 0;
            }
            memset(c, 0, sizeof(c));
            for (int i = 0; i < n; ++ i){
                c[nr[i][1]] ++;
            }
            for (int i = 0; i < n; ++ i){
                c[i + 1] += c[i];
            }
            for (int i = 0; i < n; ++ i){
                na[-- c[nr[i][1]]] = i;
            }
            memset(c, 0, sizeof(c));
            for (int i = 0; i < n; ++ i){
                c[nr[i][0]] ++;
            }
            for (int i = 0; i < n; ++ i){
                c[i + 1] += c[i];
            }
            for (int i = n - 1; i >= 0; -- i){
                sa[-- c[nr[na[i]][0]]] = na[i];
            }
            r[sa[0]] = 0;
            for (int i = 0; i < n - 1; ++ i){
                r[sa[i + 1]] = r[sa[i]] + (nr[sa[i]][0] != nr[sa[i + 1]][0] || nr[sa[i]][1] != nr[sa[i + 1]][1]);
            }
        }
        for (int i = 0, k = 0; i < n; ++ i){
            if (r[i]){
                int j = sa[r[i] - 1];
                while (i + k < n && j + k < n && s[i + k] == s[j + k]){
                    k++;
                }
                h[r[i]] = k;
                if (k){
                    -- k;
                }
            }
        }
    }

    int q[N], cnt[N];
    long long con[N];
    void solve(){
        scanf("%s",s);
        n = strlen(s);
        bld();
        long long ans = 0;
        int top = 0;
        for (int i = 1; i <= n; ++ i){
            con[i] = 1ll * i * (i + 1) / 2;
        }
        for (int i = 1; i < n; ++ i){
            int now = 1;
            while (top > 0 && q[top] > h[i]){
                ans += con[cnt[top]+1] * (q[top] - max(h[i], q[top-1]));
                top --;
                if (q[top] >= h[i]) cnt[top] += cnt[top+1]; else now += cnt[top+1];
            }
            while (top > 0 && q[top] == h[i]){
                now += cnt[top--];
            }
            if (h[i] > 0){
                q[++top] = h[i]; cnt[top] = now;
            }
        }
        while (top > 0){
            ans += con[cnt[top]+1] * (q[top] - q[top-1]);
            top --;
            cnt[top] += cnt[top+1];
        }
        ans += max(0, n - sa[0] - h[1]) + max(0, n - sa[n-1] - h[n-1]);
        for (int i = 1; i < n - 1; ++ i){
            ans += max(0, n - sa[i] - max(h[i], h[i+1]));
        }
        cout << ans << endl;
    }

}ly;

int main(){
 //   freopen("in", "r", stdin);
    ly.solve();
    return 0;
}
