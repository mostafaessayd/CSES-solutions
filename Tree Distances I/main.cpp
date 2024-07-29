/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1132
 */

#include <bits/stdc++.h>
 
using namespace std;
const int N = 2e5 + 1;
 
vector<int> adj[N];
int first[N];
int second[N];
int bestLength[N];
 
int main() {
  int n;
  cin >> n;
  int root = -1;
 
  for(int i = 0 ; i < n - 1 ; i++) {
    int x , y;
    cin >> x >> y;
    x--;
    y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
    if(adj[x].size() > 1) {
      root = x;
    }
    if(adj[y].size() > 1) {
      root = y;
    }
  }
  
  if(n == 1) {
    cout << "0";
    return 0;
  }
 
  if(n == 2) {
    cout << "1 1";
    return 0;
  }
 
  auto getDepths = [&](auto self , int u , int p)->int {
    if(adj[u].size() == 1) {
      return 0;
    }else {
      vector<int> d;
      for(int v : adj[u]) {
        if(v != p) {
          d.push_back(self(self , v , u) + 1);
        }
      }
 
      sort(d.rbegin() , d.rend());
 
      first[u] = d[0];
      if(d.size() > 1) {
        second[u] = d[1];
      }
 
      return first[u];
    }
  };
 
  auto bestChoise = [&](auto self , int u , int p , int top)->void{
    bestLength[u] = max(first[u] , top);
    for(int v : adj[u]) {
      if(v != p) {
        if(first[v] + 1 == first[u]) {
          self(self , v , u , max(top , second[u]) + 1);
        }else {
          self(self , v , u , bestLength[u] + 1);
        }
      }
    }
  };
 
  getDepths(getDepths , root , -1);
  bestChoise(bestChoise , root , -1 , 0);
 
  for(int i = 1 ; i <= n ; i++) {
   printf("%d " , bestLength[i - 1]);
  }
 
  return 0;
}