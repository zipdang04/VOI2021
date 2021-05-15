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

#define MAX 100001
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
int num[MAX], low[MAX];
bool isBri[MAX];
pii bridge[MAX];
int bLen = 0;
int t = 0;

void dfs(int node, int prevEdge){
	num[node] = low[node] = ++t;
	for (Node child: graph[node]){
		if (child.idx == prevEdge) continue;

		if (num[child.node])
			low[node] = min(low[node], num[child.node]);
		else{
			dfs(child.node, child.idx);
			low[node] = min(low[node], low[child.node]);
			if (num[node] < low[child.node]){
				isBri[child.idx] = true;
				bridge[++bLen] = {node, child.node};
			}
		}
	}
}

void makeNode(int node, int value){
	num[node] = value;
	for (Node child: graph[node]){
		if (num[child.node]) continue;
		if (isBri[child.idx]) continue;
		makeNode(child.node, value);
	}
}

vi dedGraph[MAX];
int cnt;
int f[MAX], g[MAX];
bool visited[MAX];

void cal(int node, int par){
	int b1 = 0, b2 = 0; visited[node] = true;
	for (int child: dedGraph[node]){
		if (child == par) continue;
		cal(child, node);

		int value = g[child] + 1;
		g[node] = max(g[node], value);
		if (value >= b1) b2 = b1, b1 = value;
		else if (value >= b2) b2 = value;
	}
	f[node] = b1 + b2;
}

main()
{
	#ifndef ONLINE_JUDGE
	freopen("construct.inp", "r", stdin);
	freopen("construct.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, _, 1, m){
		int u, v; cin >> u >> v ;
		graph[u].push_back(Node(v, _));
		graph[v].push_back(Node(u, _));
	}
	
	FOR(int, node, 1, n)
		if (!num[node]) dfs(node, 0);
	
	memset(num, 0, sizeof(num));
	FOR(int, node, 1, n)
		if (!num[node]){
			cnt++; makeNode(node, cnt);
		}
	FOR(int, i, 1, bLen){
		int u = bridge[i].fi, v = bridge[i].se;
		u = num[u], v = num[v];
		dedGraph[u].push_back(v);
		dedGraph[v].push_back(u);
	}
	
	FOR(int, i, 1, cnt){
		if (visited[i]) continue;
		cal(i, i);
	}
	int ans = 0;
	FOR(int, i, 1, n) ans = max(ans, f[i]);
	cout << ans;
}

	// read the questions and then answer it now
	// i'm sure you'll scream it out loud
	// in the coming matches of Last Match At Olympia