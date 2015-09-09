#include <cstdio>
#include <cstring>
using namespace std;

int pow(int x, int k, int mo){
    int a = 1;
    while (k){
        if (k & 1){
            a = 1ll * a * x % mo;
        }
        x = 1ll * x * x % mo;
        k >>= 1;
    }
    return a;
}

struct ColorfulLineGraphs{
    int countWays(long long n, long long k, int mo){
        long long ret = 1;
        n --;
        k %= mo;
        for (int i = 0; i < mo; ++ i){
            ret = (ret * pow((k + i * (k - 1)) % mo, n / mo + ((n % mo) >= i), mo)) % mo;
        }
        return (int) ret;
    }
}