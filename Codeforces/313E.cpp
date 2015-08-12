/*
CF-8-11 Something
*/
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
int a[100005], b[100005];
stack<int> s;
queue<int> q;
vector<int> ans;

int main(){
 //   freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    int x;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &x);
        a[x] ++;
    }
    for (int i = 0; i < n; ++ i){
        scanf("%d", &x);
        b[x] ++;
    }
    for (int i = m - 1; i >= 0; -- i){
        while (b[m - 1 - i] > 0){
            s.push(m - 1 - i);
            b[m - 1 - i] --;
        }
        while (a[i] > 0){
            if (s.size() > 0){
                ans.push_back(i + s.top()); s.pop();
            } else {
                q.push(i);
            }
            a[i] --;
        }
    }
    while (!q.empty()){
        ans.push_back(q.front() + s.top() - m);
        q.pop();
        s.pop();
    }
    sort(ans.begin(), ans.end());
    for (int i = ans.size() - 1; i >= 0; -- i){
        printf("%d ", ans[i]);
    }
    return 0;
}