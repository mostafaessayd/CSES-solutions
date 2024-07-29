/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1135
 */

#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 300000;
const int LOG = 20;
 
vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];
 
void dfs(int u, int parent) {
    up[u][0] = parent;
    for (int i = 1; i < LOG; ++i) {
        if (up[u][i-1] != -1) {
            up[u][i] = up[up[u][i-1]][i-1];
        } else {
            up[u][i] = -1;
        }
    }
 
    for (int v : adj[u]) {
        if(v == parent)
        continue;
 
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
 
int kth_ancestor(int u, int k) {
    if (k > depth[u]) return -1; 
 
    for (int i = 0; i < LOG; ++i) {
        if (k & (1 << i)) {
            u = up[u][i];
            if (u == -1) break;
        }
    }
    return u;
}
 
int LCA_OF_A_B(int a , int b) {
  int da = depth[a];
  int db = depth[b];
 
  if(da > db) {
    a = kth_ancestor(a , da - db);
  }else if(db > da) {
    b = kth_ancestor(b , db - da);
  }
  
  while(a != b) {
   int j = 19;
   while(up[a][j] == up[b][j] && j > 0) {
    j--;
   }
 
   a = up[a][j];
   b = up[b][j];
  }
 
  return a;
}
 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, q;
    cin >> n >> q;
 
    memset(up, -1, sizeof(up));
    fill(depth, depth + n, 0);
 
    for (int i = 1; i < n; ++i) {
        int x , y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
 
    dfs(0, -1);
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int g = LCA_OF_A_B(a , b);
        cout << depth[b] + depth[a] - 2 * depth[g] << '\n';
    }
 
    return 0;
}