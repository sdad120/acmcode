#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
vector<ll> ret;

void doStep(vector<ll> &h, ll step){
    int n = h.size(), flag = h[0] > 0;
    for (int i = 0; i < n; ++ i){
        int nxt = (i + 1) % n;
        int nxtFlag = h[nxt] > 0;
        if (flag){
            h[i] -= step;
            h[nxt] += step;
        }
        flag = nxtFlag;
    }
}

class FlattenOut{
public:
    vector<ll> simulateIt(vector<ll> h, ll T){
        int n = h.size();
        while (T){
            int flag = 1;
            ll step = T;
            for (int i = 0; i < n; ++ i){
                int pre = (i - 1 + n) % n;
                if (h[pre] <= 0 && h[i] > 0){
                    step = min(step, h[i]);
                }
                if (h[pre] > 0 && h[i] <= 0){
                    step = min(step, -h[i] + 1);
                }
                if (h[i] != 0 && h[i] != 1){
                    flag = 0;
                }
            }
            if (flag){
                ret.resize(n);
                for (int i = 0; i < n; ++ i){
                    ret[(i + T) % n] = h[i];
                }
                return ret;
            }
            doStep(h, step);
            T -= step;
        }
        for (int i = 0; i < n; ++ i){
            cout << i << " " << h[i] << endl;
        }
        return h;
    }
};