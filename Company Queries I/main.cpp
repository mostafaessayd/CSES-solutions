/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1687
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
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, q, x;
    cin >> n >> q;
 
    memset(up, -1, sizeof(up));
    fill(depth, depth + n, 0);
 
    for (int i = 1; i < n; ++i) {
        cin >> x;
        x--;
        adj[x].push_back(i);
    }
 
    dfs(0, -1);
 
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        int ancestor = kth_ancestor(a, b);
        cout << (ancestor == -1 ? -1 : ancestor + 1) << '\n';
    }
 
    return 0;
}