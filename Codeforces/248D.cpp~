/*
CF-8-2 Something
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int n, t, lasthouse, tot;
#define N 500005
char a[N];
int s[N];
set<int> next;

int remain(int k, int sum, int tot){
    int l = k + 1, r = n - 1;
    while (l < r){
        int mid = (l + r ) / 2;
        if (s[mid] - s[k] >= tot) r = mid; else l = mid + 1;
    }
    if (s[l] - s[k] < tot) return 0;
    return (max(l, lasthouse) - k) * 2 + sum <= t;
}

int ok(int have){
    for (int i = 0; i < n; ++ i){
        if (a[i] != 'S') continue;
        next.insert(i);
    }
    long long sum = 0;
    int right = -1, left = -1, now = tot;
    for (int i = 0; i <= max(lasthouse, right); ++ i){
        sum ++;
        if (a[i] == '.') continue;
        if (a[i] == 'S'){
            if (right != i){
                if (next.count(i)){
                    have ++;
                    next.erase(i);
                }
            } else {
                if (lasthouse <= right){
                    sum -= right - left;
                }
                sum += (right - left) * 2;
                right = -1;
            }
        }
        if (a[i] == 'H'){
            if (have){
                have --;
            } else {
                if (next.size() == 0) return 0;
                int near = (*next.begin());
                next.erase(near);
                if (right == -1){
                    left = i;
                    if (remain(i, sum, now)) return 1;
                }
                right = near;
            }
            now --;
        }
    }
    return sum <= t;
}

int main(){
   // freopen("in", "r", stdin);
    scanf("%d%d", &n, &t);
    scanf("%s", a);
    for (int i = 0; i < n; ++ i){
        if (a[i] == 'H'){
            lasthouse = i;
            tot ++;
        }
        s[i] = (i > 0 ? s[i-1] : 0) + (a[i] == 'S');
    }
    int l = 0, r = n;
    while (l < r){
        int mid = (l + r) / 2;
        if (ok(mid)) r = mid; else l = mid + 1;
    }   
    if (ok(l)){
        printf("%d\n", l);
    } else {
        puts("-1");
    }
    return 0;
}
