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

    int get(int a, int b){
        int k = 0;
        while ((1 << (k + 1)) <= b - a + 1) ++ k;
        return min(dp[a][k], dp[b - (1 << k) + 1][k]);
    }

    void solve(){
        scanf("%s",s);
        n = strlen(s);
        bld();
    }

};
