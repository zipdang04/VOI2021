#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 1000001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

template <typename T> inline void read(T &x)
{
    char c;
    bool neg = 0;
    while ((!isdigit(c = getchar())) && (c != '-'));
    if (c == '-')
    {
        neg = 1;
        c = getchar();
    }
    x = c - 48;
    while(isdigit(c = getchar())) x = x * 10 + c - 48;
    if (neg) x =- x;
}

vector<pii> graph[MAX];
int n, m;
int arr[MAX], len;
bool visited[MAX];

bool dfs(const int threshold){
	memset(visited, false, sizeof(visited));
	arr[++len] = 1;
	while (len){
		int node = arr[len--];
		for (pii child: graph[node]){
			if (child.fi > threshold) continue;
			if (visited[child.se]) continue;

			visited[child.se] = true;
			arr[++len] = child.se;
		}
	}
	return visited[n];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef ONLINE_JUDGE
	freopen("comnet.inp", "r", stdin);
	freopen("comnet.out", "w", stdout);
	#endif

	read(n); read(m);
	FOR(int, _, 1, m){
		int u, v; read(u); read(v);
		graph[u].push_back({_, v});
	}

	int l = 1, r = m, ans = -1;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (dfs(mid))
			ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans;
	
	// priority_queue<pii, vector<pii>, greater<pii>> pq;
	// ans[1] = 0, pq.push({0, 1});
	// while (!pq.empty()){
	// 	pii curr = pq.top(); pq.pop();
	// 	int node = curr.se, val = curr.fi;
	// 	if (ans[node] != val) continue;
		
	// 	for (pii now: graph[node]){
	// 		int child = now.se, num = max(val, now.fi);
	// 		if (num < ans[child])
	// 			ans[child] = num, pq.push({num, child});
	// 	}
	// }
	// if (ans[n] == INT32_MAX)
	// 	cout << -1;
	// else 
	// 	cout << ans[n];
}