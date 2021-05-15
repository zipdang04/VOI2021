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
	int node, idx;
	Node() {node = idx = 0;}
	Node(int node, int idx) {this -> node = node, this -> idx = idx;}
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

int n, m;
vg graph[MAX];
vi tree[MAX];

int num[MAX], low[MAX], t;
bool br[MAX];
int arti[MAX];
void tarjan(int node, int parent){
	num[node] = low[node] = ++t;
	if (node != parent) tree[parent].push_back(node);
	int numOfChild = 0;

	for (Node child: graph[node]){
		if (child.node == parent) continue;
		if (num[child.node])
			low[node] = min(low[node], num[child.node]);
		else {
			numOfChild++;
			tarjan(child.node, node);
			low[node] = min(low[node], low[child.node]);

			if (low[child.node] >= num[child.node])
				br[child.idx] = true;
			
			if (node == parent){
				if (numOfChild > 1) 
					arti[node] = true;
			} else {
				if (low[child.node] >= num[node])
					arti[node] = true;
			}
		}
	}
}

bool visited[MAX];
int dfs(int node){
	visited[node] = true;
	int ans = 1;

	for (Node child: graph[node]){
		if (visited[child.node] || arti[child.node]) continue;
		ans += dfs(child.node);
	}
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, i, 1, m){
		int u, v; cin >> u >> v;
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
	}

	tarjan(1, 1);
	dfs(1);

	ll answer = 0;
	FOR(int, node, 1, n)
		if (!visited[node] && !arti[node]){
			ll x = dfs(node);
			cerr << node << ' ' << x << '\n';
			answer += x * (n - x - 1);
		}
	answer /= 2;
	cout << fixed << setprecision(2) << answer / ld(n);
}