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

// /*
struct Node
{
	int node, time, low;
	Node() {node = time = low = 0;}
	Node(int node, int time, int low) {this -> node = node, this -> time = time, this -> low = low;}
};
typedef vector<Node> vg;
// */

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

int n, k;
vg graph[MAX];

int f[MAX];
int best[MAX];

void preDfs(int node, int parent, int v1, int v2){
	f[node] = v1, best[node] = v2;
	for (Node child: graph[node]){
		if (child.node == parent) continue;
		preDfs(child.node, node, v1 + child.time, v2 + child.low);
		f[node] = max(f[node], f[child.node]);
		best[node] = max(best[node], best[child.node]);
	}
}

int dfs(int node, int parent, int thres, int preMinus){
	if (f[node] - preMinus <= thres) return 0;

	int answer = 0;
	for (Node child: graph[node]){
		if (child.node == parent) continue;
		f[child.node] -= preMinus;
		int maxMinus = child.time - child.low;

		if (f[child.node] - thres <= maxMinus) 
			answer += max(0, f[child.node] - thres);
		else
			answer += maxMinus + dfs(child.node, node, thres, preMinus + maxMinus);
	}
	return answer;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; i++)
	{
		int u, v, a, b; cin >> u >> v >> a >> b;
		graph[u].push_back(Node(v, a, b));
		graph[v].push_back(Node(u, a, b));
	}

	preDfs(1, 0, 0, 0);
	FOR(int, i, 1, n) cerr << f[i] << ' '; cerr << '\n';
	int left = best[1], right = f[1], ans = f[1];
	while (left <= right){
		int mid = (left + right) >> 1;
		if (dfs(1, 0, mid, 0) <= k)
			ans = mid, right = mid - 1;
		else 
			left = mid + 1;
	}
	cout << ans;
}