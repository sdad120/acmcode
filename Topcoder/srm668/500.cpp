/*
 * TC
 * Author: Andy Y.F. Huang
 */
 
#include <bits/stdc++.h>
 
using namespace std;
 
struct WalkingToSchool {
  string canWalkExactly(int N, vector<int> from, vector<int> to);
};
 
const int MAX = 2111;
vector<int> adj[MAX];
int dist[MAX];
bool was[MAX][MAX];
int N;
 
bool can(int st, int ed) {
  memset(dist, 0x3F, sizeof(dist));
  int C = -1;
  {
    queue<int> que;
    que.push(st);
    dist[st] = 0;
    while (!que.empty()) {
      const int at = que.front();
      que.pop();
      for (const int& to : adj[at]) {
        if (dist[at] + 1 < dist[to]) {
          que.push(to);
          dist[to] = dist[at] + 1;
        } else if (to == st) {
          C = dist[at] + 1;
        }
      }
    }
  }
  if (C == -1) {
    return false;
  }
  memset(was, false, sizeof(was));
  queue<pair<int, int> > que;
  que.push(make_pair(st, 0));
  was[st][0] = true;
  while (!que.empty()) {
    const int at = que.front().first, mod = que.front().second;
    que.pop();
    for (const int& to : adj[at]) {
      if (!was[to][(mod + 1) % C]) {
        was[to][(mod + 1) % C] = true;
        que.push(make_pair(to, (mod + 1) % C));
      }
    }
  }
  for (int c = 0; c < C; ++c) {
    if (!was[ed][c]) {
      return false;
    }
  }
  return true;
}
 
string WalkingToSchool::canWalkExactly(int N_, vector<int> from, vector<int> to) {
  N = N_;
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
  }
  for (int i = 0; i < (int) from.size(); ++i) {
    adj[from[i]].push_back(to[i]);
  }
  if (can(0, 1) && can(1, 0)) {
    return "Freedom";
  } else {
    return "Chores";
  }
}
