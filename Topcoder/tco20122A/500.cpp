#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const ll inf = 1e18;
long long dp[55][55];
ll x[55];

class CucumberWatering{
public:
    ll theMin(vector<int> _x, int K){
        int n = _x.size() + 2;
        x[0] = -inf; x[n-1] = inf;
        for (int i = 1; i < n - 1; ++ i){
            x[i] = _x[i-1];
        }
        sort(x, x + n);
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j <= K + 1; ++ j){
                dp[i][j] = inf;
            }
        }
        //dp[0][K+1] = 0;
        for (int i = 0; i <= K + 1; ++ i){
            dp[0][i] = 0;
        }
        for (int last = 1; last < n; ++ last){
            for (int remainK = 0; remainK <= K; ++ remainK){
                for (int prelast = 0; prelast < last; ++ prelast){
                    ll old = dp[prelast][remainK + 1];
                    if (old >= inf) continue;
                    for (int i = 0; i + 1< _x.size(); ++ i){
                        ll left = _x[i];
                        ll right = _x[i+1];
                        if (left > right) swap(left, right);
                        if (left > x[prelast] && left <= x[last]){
                            if (right <= x[last]){
                                old += min(right - left, left - x[prelast] + x[last] - right);
                            } else {
                                old += min(left - x[prelast], x[last] - left);
                            }
                        } else 
                        if (left <= x[last]){
                            if (right > x[prelast] && right <= x[last]){
                                old += min(x[last] - right, right - x[prelast]);
                            }
                        }
                    }
                    dp[last][remainK] = min(dp[last][remainK], old);
                }
            }
        }
        for (int i = 0; i < n; ++ i){
            for (int j = 0; j <= K; ++ j){
                cout << i << " " << j << " " << dp[i][j] << endl;
            }
        }
        return dp[n-1][0];
    }
};