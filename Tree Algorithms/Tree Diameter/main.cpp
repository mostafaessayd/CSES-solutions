/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1131
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

vector<vector<int>> adj;
 int cur = 0;

int dfs(int u, int y)
{
    if(adj[u].size() == 1)
    {
        return 0;
    }

    vector<int> depths;

    for(int p : adj[u])
    {
        if(p != y)
        {
            int v = dfs(p, u) + 1;
            depths.push_back(v);
        }
    }

    sort(depths.rbegin(), depths.rend());

    int ans = 0;
    int k = 0;
    for(int ind : depths)
    {
        ans += ind;
        k++;
        if(k == 2)
            break;
    }

    cur = max(cur,ans);

    return depths[0];
}

void answer()
{
    int n, m;
    cin >> n;

    if(n == 2)
    {
        cout << "1\n";
        return;
    }

    adj.resize(n);

    for(int i = 0 ; i < n - 1 ; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }


    for(int i = 0 ; i < n ; i++)
        if(adj[i].size() > 1)
        {
            dfs(i, -1);
            break;
        }

    cout << cur;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;

    while (T--)
    {
        answer();
    }

    return 0;
}
