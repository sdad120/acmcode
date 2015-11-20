//这个剩余定理的版本解决了long long 乘 long long的爆炸问题
//用快速加代替了直接的乘法

typedef long long ll;

ll get(ll x, ll y, ll M){
    ll a = 0;
    while (y){
        if (y & 1){
            a = (a + x) % M;
        }
        x = (x + x) % M;
        y >>= 1;
    }
    return a;
}

ll china(ll n, ll a[], ll m[]){
    ll M = 1, d, y, x = 0;
    for (int i = 0; i < n; ++ i) M *= m[i];
    for (int i = 0; i < n; ++ i){
        ll w = M / m[i];
        gcd(m[i], w, d, d, y);
        //x = (x + y * w * a[i]) % M;
        x = (x + get(get(y, w, M), a[i], M)) % M;
    }
    return (x + M) % M;
}
