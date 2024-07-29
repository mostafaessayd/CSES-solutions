/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1130
 */

#include <bits/stdc++.h>
 
using namespace std;
const int maxN = 2e5+1;
 
int n, a, b, ans;
bool vis[maxN];
vector<int> adj[maxN];
 
void dfs(int u = 1, int p = 0){
    for(int v : adj[u])
        if(v != p)
            dfs(v, u);
 
    if(!vis[p] && !vis[u] && p != 0){
        vis[p] = vis[u] = true;
        ans++;
    }
}
 
int main(){
    cin >> n;
    
    for(int i = 0; i < n - 1 ; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs();

    cout << ans;
}