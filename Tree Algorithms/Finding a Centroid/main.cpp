/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/2079
 */


#include <iostream>
#include <vector>
#include <set>
 
using namespace std;
typedef long long ll;
const int maxN = 2e5 + 5;
 
vector<int> adj[maxN];
  
int sz[maxN];
int ans = -1;
int n;
void dfs(int u , int p) {
    sz[u] = 1;
	bool okey = true;
    for(int v : adj[u]) {
        if(v != p) {
            dfs(v , u);
            sz[u] += sz[v];
			okey &= (sz[v] <= n / 2);
        }
    }
 
	if(okey && sz[u] >= n / 2) {
		ans = u + 1;
	}
}
 
int main()
{
	cin >> n;
 
	for (int i = 1; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
 
    dfs(0 , -1);
 
    cout << ans;
 
    return 0;
}