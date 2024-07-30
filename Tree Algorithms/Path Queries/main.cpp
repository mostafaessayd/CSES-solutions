/**
 * created by : cidi mohamed mostepha
 * link : https://cses.fi/problemset/task/1138
 */

#include<bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
const int N = 2e5 + 1;
 
vector<ll> vec(N);
vector<int> adj[N];
vector<ll> segment(2 * N);
int timer = 0;
ll en[N] , ex[N];
ll prefixeSum[8 * N];
 
void build(int l, int r, int pos , vector<ll>& vec)
{
	if (l == r)
	{
		prefixeSum[pos] = vec[l];
	}
	else
	{
		int mid = (l + r) / 2;
		build(l, mid, pos * 2 , vec);
		build(mid + 1, r, pos * 2 + 1 , vec);
		prefixeSum[pos] = prefixeSum[pos * 2] + prefixeSum[pos * 2 + 1];
	}
}
 
ll getSum(int l, int r, int a, int b, int pos)
{
	if (a > r || l > b)
	{
		return 0;
	}
 
	if (l >= a && r <= b)
	{
		return prefixeSum[pos];
	}
 
	int mid = (l + r) / 2;
	ll p1 = getSum(l, mid, a, b, pos * 2);
	ll p2 = getSum(mid + 1, r, a, b, pos * 2 + 1);
 
	return p1 + p2;
}
 
void update(int l, int r, int x, ll y, int pos , vector<ll>& vec)
{
	if (l == r)
	{
		prefixeSum[pos] -= vec[x];
		prefixeSum[pos] += y;
		vec[x] = y;
	}
	else
	{
		int mid = (l + r) / 2;
		if (x <= mid)
		{
			update(l, mid, x, y, pos * 2 , vec);
		}
		else
		{
			update(mid + 1, r, x, y, pos * 2 + 1 , vec);
		}
		prefixeSum[pos] = prefixeSum[pos * 2] + prefixeSum[pos * 2 + 1];
	}
}
 
void dfs(int u , int p) {
 
    en[u] = timer++;
    segment[en[u]] = vec[u]; 
 
    for(int v : adj[u]) {
        if(v != p) {
            dfs(v , u);
        }
    }
 
    ex[u] = timer++;
    segment[ex[u]] = -vec[u];
}
 
int main() {
    int n , q;
    cin >> n >> q;
    for(int i = 0 ; i < n ; i++) {
        cin >> vec[i];
    }
 
    for(int i = 0 ; i < n - 1 ; i++) {
        int x , y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
 
    dfs(0 , -1);
    build(0 , ex[0] , 1 , segment);
 
    while(q--) {
        int s;
        cin >> s;
        if(s == 1) {
            int a , b;
            cin >> a >> b;
            update(0 , ex[0] , en[a - 1] , b , 1 , segment);
            update(0 , ex[0] , ex[a - 1] , -b , 1 , segment);
        }else {
            int b;
            cin >> b;
            cout << getSum(0 , ex[0] , 0 , en[b - 1] , 1) << '\n';
        }
    }
}

