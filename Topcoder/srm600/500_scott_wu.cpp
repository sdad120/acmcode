//from scott_wu
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
class PalindromeMatrix {
public:
  int minChange(vector <string>, int, int);
};
 
int N, M;
bool use[100];
int c1[100], c2[100];
int dp[100];
 
int PalindromeMatrix::minChange(vector <string> A, int nval, int mval) {
  N = A.size();
  M = A[0].length();
  
  int best = 100000;
  for (int i = 0; i < (1 << N); i++)
  {
    int cnt = 0;
    for (int j = 0; j < N; j++)
    {
      if (i & (1 << j))
        cnt++;
      use[j] = ((i & (1 << j)) ? true : false);
    }
    
    if (cnt != nval) continue;
    
    int tot = 0;
    for (int j = 0; j < N; j++)
      if (use[j])
      {
        for (int k = 0; k < M / 2; k++)
          if (A[j][k] != A[j][M-1-k])
            tot++;
      }
    
    for (int j = 0; j < M; j++) // calculate cost for col j and ! M-1-j
    {
      c1[j] = 0;
      for (int k = 0; k < N / 2; k++)
      {
        int u = k, v = N - 1 - k;
        if (use[v] && !use[u])
          swap (u, v);
        
        if (use[u] && use[v])
        {
          if (A[u][j] == A[u][M-1-j] && A[v][j] == A[v][M-1-j] && A[u][j] != A[v][j])
            c1[j] += 2;
        }
        else if (use[u])
        {
          if (A[u][j] == A[u][M-1-j] && A[u][j] != A[v][j])
            c1[j]++;
        }
        else
        {
          if (A[u][j] != A[v][j])
            c1[j]++;
        }
      }
    }
    
    for (int j = 0; j < M / 2; j++) // calculate cost for col j and M-1-j
    {
      c2[j] = 0;
      
      int x = j, y = M - 1 - j;
      for (int k = 0; k < N / 2; k++)
      {
        int u = k, v = N - 1 - k;
        if (use[v] && !use[u])
          swap (u, v);
        
        if (use[u] && use[v])
        {
          if (A[u][x] == A[u][y] && A[v][x] == A[v][y])
            if (A[u][x] != A[v][x])
              c2[j] += 2;
        }
        else if (use[u])
        {
          if (A[u][x] == A[u][y])
          {
            if (A[v][x] != A[u][x]) c2[j]++;
            if (A[v][y] != A[u][y]) c2[j]++;
          }
          else
          {
            if (A[v][x] != A[v][y]) c2[j]++;
          }
        }
        else
        {
          if (A[u][x] != A[v][x])
            c2[j]++;
          if (A[u][y] != A[v][y])
            c2[j]++;
        }
      }
    }
    
    for (int j = 0; j < 100; j++)
      dp[j] = 100000;
    dp[0] = tot;
    
    for (int j = 0; j < M / 2; j++)
    {
      for (int k = 20; k >= 0; k--)
      {
        dp[k+2] = min (dp[k+2], dp[k] + c2[j]);
        dp[k+1] = min (dp[k+1], dp[k] + c1[j]);
        dp[k+1] = min (dp[k+1], dp[k] + c1[M-1-j]);
      }
    }
    
    best = min (best, dp[mval]);
    
    /*if (dp[mval] == 12)
    {
      cout << tot << " " << i << "\n";
    }*/
  }
  return best;
}