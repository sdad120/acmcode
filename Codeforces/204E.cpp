/*
CF-8-16 Something
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200005
#define inf 168430090 

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

    int dp[N][20]; 
    
    void ready(){
        for (int i = 0; i < n; ++ i) dp[i][0] = h[i];
        for (int j = 1; (1 << j) <= n; ++ j){
            for (int i = 0; i + (1 << j) - 1 < n; ++ i){
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int Log[N];

    int get(int a, int b){
        int k = Log[b-a+1];
        //while ((1 << (k + 1)) <= b - a + 1) ++ k;
        return min(dp[a][k], dp[b - (1 << k) + 1][k]);
    }

    int f[N], p[N], st[N], to[N], m, k;
    long long ans[N];

    int ok(int j, int M){
        int left = 1, right = r[j];
        while (left < right){
            int mid = (left + right) / 2;
            if (get(mid, r[j]) >= M) right = mid; else left = mid + 1;
        }
        if (left != r[j] || h[left] >= M){
            left --;
        }
        int from = left;
        left = r[j] + 1, right = n;
        while (left < right){
            int mid = (left + right + 1) / 2;
            if (get(r[j] + 1, mid) >= M) left = mid; else right = mid - 1;
        }
        if (h[left] < M){
            left --;
        }
        return to[from] <= left;
    }

    void solve(){
        scanf("%d%d", &m, &k);
        n = 0;
        for (int i = 0; i < m; ++ i){
            st[i] = n;
            scanf("%s", s + n);
            n += strlen(s + n);
            for (int j = st[i]; j < n; ++ j){
                f[j] = i;
            }
            s[n++] = '#';
        }
        st[m] = n;
        bld();
        ready();
        int right = 0, sum = 0;
        memset(p, 0, sizeof(p));
        for (int l = 0; l < n; ++ l){
            while (right < n && sum != k){
                if (s[sa[right]] != '#'){
                    if (p[f[sa[right]]] == 0){
                        sum ++;
                    }
                    p[f[sa[right]]] ++;
                }
                right ++;
            }
            if (sum != k) to[l] = inf; else to[l] = right - 1;
            if (s[sa[l]] != '#'){
                p[f[sa[l]]] --;
                if (p[f[sa[l]]] == 0){
                    sum --;
                }
            }
        }
        for (int i = 1; i <= n; ++ i){
            Log[i] = log(i * 1.0) / log(2.0);
        }

        for(int i = 0; i < m; ++ i){
            ans[i] = 0;
            for (int j = st[i]; j < st[i+1] - 1; ++ j){
                int L = 1, R = st[i+1] - j - 1;
                while (L < R){
                    int M = (L + R + 1) / 2;
                    if (ok(j, M)) L = M; else R = M - 1;
                }
                if (ok(j, L)) ans[i] += L;
            }
        }
        for (int i = 0; i < m; ++ i){
            printf("%I64d\n", ans[i]);
        }
    }

}ly;

int main(){
   // freopen("in", "r", stdin);
    ly.solve();
    return 0;
}