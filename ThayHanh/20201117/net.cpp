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

int n, m, k, l;
bool a[MAX], b[MAX];
vg graph[MAX];

int num[MAX], low[MAX], currTime = 0;
pii bridge[MAX]; int brLen = 0;
bool isBr[MAX];

void tarjan(int node, int parent){
	// cerr << node << ' ' << parent << '\n';
	num[node] = low[node] = ++currTime;

	for (Node child: graph[node]){
		if (child.node == parent) continue;
		
		if (num[child.node])
			low[node] = min(low[node], num[child.node]);
		else {
			tarjan(child.node, node);
			low[node] = min(low[node], low[child.node]);
			if (num[node] < low[child.node])
				isBr[child.idx] = true,
				bridge[++brLen] = {node, child.node};
		}
	}
}

int cnt = 0;
int cntA[MAX], cntB[MAX];
int root[MAX]; bool isRoot[MAX];
vi ded[MAX];

void make(int node, int r, int value){
	num[node] = value, root[node] = r;
	cntA[value] += a[node];
	cntB[value] += b[node];
	for (Node child: graph[node]){
		if (num[child.node]) continue;
		if (isBr[child.idx]) continue;
		make(child.node, r, value);
	}
}

void build(int node, int parent){
	for (int child: ded[node]){
		if (child == parent) continue;
		build(child, node);

		cntA[node] += cntA[child];
		cntB[node] += cntB[child];
	}
}

int answer = 0;

void dfs(int node, int parent, int root){
	for (int child: ded[node]){
		if (child == parent) continue;

		if (!cntA[child] || !(cntA[root] - cntA[child]) || !cntB[child] || !(cntB[root] - cntB[child]))
			answer++;

		dfs(child, node, root);
	}
}

main()
{
	#ifndef ONLINE_JUDGE
	freopen("net.inp", "r", stdin);
	freopen("net.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k >> l;
	FOR(int, i, 1, k) {int num; cin >> num; a[num] = true;}
	FOR(int, i, 1, l) {int num; cin >> num; b[num] = true;}
	FOR(int, i, 1, m){
		int u, v; cin >> u >> v;
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
	}
	FOR(int, i, 1, n)
		if (!num[i])
			isRoot[i] = true, tarjan(i, 0);
	// cerr << "//";
	
	memset(num, 0, sizeof(num));
	FOR(int, i, 1, n)
		if (!num[i])
			make(i, i, ++cnt);
	n = cnt;
	FOR(int, e, 1, brLen){
		int u = bridge[e].fi, v = bridge[e].se;
		u = num[u], v = num[v];
		ded[u].push_back(v);
		ded[v].push_back(u);
	}

	FOR(int, i,1, n)
		if (isRoot[i])
			build(i, i), dfs(i, i, i);
	cout << answer;
}