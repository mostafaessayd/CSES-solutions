/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1674
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

vector<vector<int>> adj;
vector<int> dp;

int dfs(int u)
{
    if (adj[u].size() == 0)
    {
        dp[u] = 0;
        return 0;
    }
    else
    {
        int ans = 0;
        for (int v : adj[u])
        {
            ans += dfs(v) + 1;
        }

        dp[u] = ans;
        return ans;
    }
}

void answer()
{
    int n;
    cin >> n;

    adj.resize(n);
    dp.resize(n, 0);

    for (int i = 1; i < n; i++)
    {
        int x;
        cin >> x;
        x--;
        adj[x].push_back(i);
    }

    dp[0] = dfs(0);

    for (int i = 0; i < n; i++)
    {
        cout << dp[i] << ' ';
    }
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
