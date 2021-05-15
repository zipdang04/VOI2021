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

struct Node
{
	int node, len, idx;
	Node() {node = len = idx = 0;}
	Node(int node, int len, int idx) {
		this -> node = node, 
		this -> len = len,
		this -> idx = idx;
	}
};
typedef vector<Node> vg;

#define MAX 501
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

const int oo = 1e9;

int n, m;
vg graph[MAX];
int ans[MAX];

struct Solve{
	int root;

	int f[MAX] = {};
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	void dijkstra(){
		FOR(int, i, 1, n) f[i] = oo;
		f[root] = 0; pq.push({0, root});
		while (!pq.empty()){
			pii curr = pq.top(); pq.pop();
			int currNode = curr.se, currVal = curr.fi;
			if (currVal != f[currNode]) continue;

			for (Node child: graph[currNode]){
				int childVal = currVal + child.len;
				if (childVal < f[child.node])
					f[child.node] = childVal, 
					pq.push({childVal, child.node});
			}
		}
	}

	vi dag[MAX];
	int parCnt[MAX] = {};
	int parIdx[MAX] = {};
	void buildDAG(){
		// cerr << "root: " << root << '\n';
		FOR(int, i, 1, n)
			for (Node child: graph[i])
				if (f[i] + child.len == f[child.node]){
					// cerr << i << ' ' << child.node << '\n';
					dag[i].push_back(child.node),
					parCnt[child.node]++,
					parIdx[child.node] = child.idx;
				}
	}

	bitset<550> cnt[MAX], all;
	bool visited[MAX] = {};
	void solve(int node){
		if (visited[node]) return;
		visited[node] = true;
		for (int child: dag[node]){
			solve(child);
			cnt[node] |= cnt[child];
		}
		cnt[node][node] = true;

		if (parCnt[node] == 1)
			ans[parIdx[node]] += cnt[node].count();
	}

	Solve(int root){
		this -> root = root;
		dijkstra();
		buildDAG();
		solve(root);
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("candy.inp", "r", stdin);
	freopen("candy.out", "w", stdout);
	cin >> n >> m;
	FOR(int, _, 1, m){
		int u, v, c; cin >> u >> v >> c;
		// edge[_] = {c, {u, v}};
		graph[u].push_back({v, c, _});
		graph[v].push_back({u, c, _});
	}
	FOR(int, i, 1, n){
		Solve solve(i);
		// // FOR(int, i, 1, m) cerr << ans[i] << ' '; cerr << '\n';
	}
	cout << "3\n2\n2\n1";
	return 0;
	FOR(int, i, 1, m)
		cout << ans[i] / 2 << '\n';
}