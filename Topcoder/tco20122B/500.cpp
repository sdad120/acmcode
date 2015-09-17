#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int pos[55];
int dp[55][55], sum[55][55];

class HeavyBooks{
public:
    vector<int> findWeight(vector<int> books, vector<int> moves){
        int n = books.size();
        int m = moves.size();
        sort(books.begin(), books.end());
        for (int i = 1; i <= moves[0]; ++ i){
            pos[i] = 1;
        }
        for (int i = 1; i < m; ++ i){
            if (i & 1){
                for (int j = 1; j <= moves[0] && moves[i]; ++ j){
                    if (pos[j]){
                        pos[j] ^= 1;
                        moves[i] --;
                    }
                }
            } else {
                for (int j = 1; j <= moves[0] && moves[i]; ++ j){
                    if (pos[j] == 0){
                        pos[j] ^= 1;
                        moves[i] --;
                    }
                }
            }
        }   
        for (int i = 1; i <= moves[0]; ++ i){
            if (pos[i] == 0) pos[i] = -1;
            printf("%d %d\n", i, pos[i]);
        }
        memset(dp, -10, sizeof(dp));
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < n; ++ i){
            dp[1][i] = pos[1] * books[i];
            sum[1][i] = books[i];
        }
        for (int i = 2; i <= moves[0]; ++ i){
            for (int j = 0; j < n; ++ j){
                for (int k = j + 1; k < n; ++ k){
                    int update = dp[i-1][k] + pos[i] * books[j];
                    if (update > dp[i][j] || (update == dp[i][j] && sum[i-1][k] + books[j] > sum[i][j])){
                        dp[i][j] = update;
                        sum[i][j] = sum[i-1][k] + books[j];
                    }
                }
            }
        }
        int ans = -168430090, ansSum = 0;
        for (int i = 0; i < n; ++ i){
            if (dp[moves[0]][i] > ans || (ans == dp[moves[0]][i] && ansSum < sum[moves[0]][i])){
                ans = dp[moves[0]][i];
                ansSum = sum[moves[0]][i];
            }
        }
        vector<int> ret;
        ret.push_back((ansSum - ans) / 2);
        ret.push_back(ansSum - ret[0]);
        return ret;
    }
};
