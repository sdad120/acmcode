/*
CF-8-16 Something
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long t, a, b;
long long c[105], tot;

int ok(long long a, long long b){
    if (a == 1){
        return 0;
    }
    tot = 0;
    while (b){
        c[tot++] = b % a;
        b /= a;
    }
    long long T = 1;
    for (int i = 0; i < tot; ++ i){
        if (a < T * c[i]){
            return 0;
        }
        a -= T * c[i];
        T *= t;
    }
    return a == 0;
}

int main(){
    //freopen("in", "r", stdin);
    cin >> t >> a >> b;
    int ans = 0;
    if (t == 1){
        if (a == 1){
            if (b == 1){
                puts("inf");
            } else {
                puts("0");
            }
        } else {
            if (ok(a, b)){
                ans ++;
            }
            if (b > 1){
                while (b % a == 0){
                    b /= a;
                }
                if (b == 1){
                    ans ++;
                }
            }
            printf("%d\n", ans);
        }
    } else {
        if (a == b){
            ans ++;
        }
        if (ok(a, b)){
            ans ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}