/*
CF-8-16 Something
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long n, sx, sy, dx, dy, x, y, t;

struct mat{
    long long a[6][6];
}A, B;

mat mul(const mat&A, const mat&B){
    mat C;
    for (int i = 0; i < 6; ++ i){
        for  (int j = 0; j < 6; ++ j){
            C.a[i][j] = 0;
            for (int k = 0; k < 6; ++ k){
                C.a[i][j] += A.a[i][k] * B.a[k][j] % n;
            }
            C.a[i][j] %= n;
        }
    }
    return C;
}

void bld(){
    B.a[0][0] = 2; B.a[1][0] = 1; B.a[2][0] = 1; B.a[4][0] = 1; B.a[5][0] = 2;
    B.a[0][1] = 1; B.a[1][1] = 2; B.a[3][1] = 1; B.a[4][1] = 1; B.a[5][1] = 2;
    B.a[0][2] = 1; B.a[1][2] = 1; B.a[2][2] = 1; B.a[4][2] = 1; B.a[5][2] = 2;
    B.a[0][3] = 1; B.a[1][3] = 1; B.a[3][3] = 1; B.a[4][3] = 1; B.a[5][3] = 2;
    B.a[4][4] = 1; B.a[5][4] = 1;
    B.a[5][5] = 1;
    for (int i = 0; i < 6; ++ i){
        A.a[i][i] = 1;
    }
    while (t){
        if (t&1){
            A = mul(A, B);
        }
        B = mul(B, B);
        t >>= 1;        
    }
    -- sx; -- sy;
    x = sx * A.a[0][0] % n + sy * A.a[1][0] % n + dx * A.a[2][0] % n + dy * A.a[3][0] % n + A.a[5][0];
    x %= n; if (x < 0) x += n;
    y = sx * A.a[0][1] % n + sy * A.a[1][1] % n + dx * A.a[2][1] % n + dy * A.a[3][1] % n + A.a[5][1];
    y %= n; if (y < 0) y += n;
}

int main(){
   // freopen("in", "r", stdin);
    cin >> n >> sx >> sy >> dx >> dy >> t;
    bld();
    cout << x + 1 << " " << y + 1 << endl;
    return 0;
}