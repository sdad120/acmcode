#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n, c;
ll b[22], v[22], s[22];
int id[22];

int cmp(int x, int y){
    return v[x] < v[y];
}

int main(){
  cin >> n >> c;
  for (int i = 0; i < n; ++ i){
    cin >> v[i] >> b[i];
    id[i] = i;
  }
  sort(id, id + n, cmp);
  ll ans = 0;
  while (1){
    for (int i = 0; i < n; ++ i){
        s[i] = 0;
    }
    ll remain = c;
    for (int i = n - 1; i >= 0; -- i){
        int k = id[i];
        s[k] = min(remain / v[k], b[k]);
        remain -= s[k] * v[k];
    }
    if (remain > 0){
        for (int i = 0; i < n; ++ i){
            int k = id[i];
            if (b[k] - s[k]){
                s[k] ++;
                remain -= v[k];
                break;
            }
        }
    }
    ll now = 1e16;
    for (int i = 0; i < n; ++ i){
        if (s[i]) now = min(now, b[i] / s[i]);
    }
    if (now == 0 || remain > 0) break;
    ans += now;
    for (int i = 0; i < n; ++ i){
        b[i] -= s[i] * now;
    }
  }
  cout << ans << endl;
  return 0;
}
