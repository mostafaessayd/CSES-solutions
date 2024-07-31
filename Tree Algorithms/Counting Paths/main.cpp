/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1136
 */

#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 1;

int up[N][20];
vector<int> adj[N];
vector<int> depth(N);
vector<int> answer(N);

void remp_up(int u = 0 , int p = -1 , int d = 0) {
    depth[u] = d;

    if(p != -1) {
        up[u][0] = p;
    }

    for(int i = 1 ; i < 20 ; i++) {
        if(up[u][i - 1] != -1) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        } else {
            up[u][i] = -1;
        }
    }

    for(int v : adj[u]) {
        if(v != p) {
            remp_up(v , u , d + 1);
        }
    }
}

int get_kth_ancestor(int u , int k) {
    for(int i = 0 ; i < 20 ; i++) {
        if(k & (1 << i)) {
            u = up[u][i];
        }
        if(u == -1)
         break;
    }

    return u;
}

int get_LCA_Of(int u , int v) {
    if(depth[u] > depth[v]) {
        u = get_kth_ancestor(u , depth[u] - depth[v]); 
    } else if(depth[u] < depth[v]) {
        v = get_kth_ancestor(v , depth[v] - depth[u]);
    }

    while(u != v) {
        int j = 19;
        while(up[v][j] == up[u][j] && j > 0) {
            j--;
        }

        u = up[u][j];
        v = up[v][j];
    }

    return u;
}

void dfs(int u = 0 , int p = -1) {
    for(int v : adj[u]) {
        if(v != p) {
            dfs(v , u);
            answer[u] += answer[v];
        }
    }
}

int main()
{
   int n , m;
   cin >> n >> m;
   for(int i = 0 ; i < n - 1 ; i++) {
    int x , y;
    cin >> x >> y;
    x--;
    y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
   }
   
   memset(up , -1 , sizeof(up));
   remp_up();

   while(m--) {
    int x , y;
    cin >> x >> y;
    x--;
    y--;
    answer[x]++;
    answer[y]++;
    int lca = get_LCA_Of(x , y);
    
   answer[lca]--;
    if(lca != 0) {
        answer[up[lca][0]]--;
    } 
   }

   dfs();

   for(int i = 0 ; i < n ; i++) {
    cout << answer[i] << ' ';
   }
}