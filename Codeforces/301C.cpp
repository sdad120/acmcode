/*
CF-8-11 Something
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    //freopen("in", "r", stdin);
    for (int i = 0; i < 9; ++ i){
        printf("%d??<>%d\n", i, i + 1);
    }
    printf("9??>>??0\n");
    printf("??<>1\n");
    for (int i = 0; i <= 9; ++ i){
        printf("?%d>>%d?\n", i, i);
    }
    printf("?>>??\n");
    printf(">>?\n");
    return 0;
}