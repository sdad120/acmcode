#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
vector<int> ha;
long long g[5005];

long long get(int k, long long R){
    if (k == (int)ha.size()){
        return R * (R + 1) / 2;
    }
    return R / ha[k] * g[k+1] + get(k + 1, R % ha[k]);
}

class ModModMod{
public:
    long long findSum(vector<int> m, int R){
        int n = m.size();
        int pre = -1;
        for (int i = 0; i < n; ++ i){
            if (pre != -1 && m[i] >= pre) continue;
            ha.push_back(m[i]);
            pre = m[i];
        }
        n = ha.size();
        g[n] = 1ll * ha[n-1] * (ha[n-1] - 1) / 2;
        for (int i = n - 1; i >= 1; -- i){
            g[i] = (ha[i-1] - 1) / ha[i] * g[i+1] + get(i + 1, (ha[i-1] - 1) % ha[i]);
        }
        for (int i = 1; i <= n; ++ i){
            cout << i << " " << g[i] << endl;
        }
        return get(0, R);
    }
};