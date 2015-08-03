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
int n;
long long a[5005], b[5005], s[5005];
int dp[5005];

int main(){
   // freopen("in", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; ++ i){
        cin >> a[i];
        b[i] = a[i]; s[i] = 0;
        while ((b[i] & 1) == 0){
            b[i] >>= 1;
            s[i] ++;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++ i){
        dp[i] = 1;
        for (int j = 0; j < i; ++ j){
            if (b[j] % b[i] == 0 && (s[j] + i - j == s[i] || i - j - 1 >= s[i])){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    printf("%d\n", n - ans);
    return 0;
}
