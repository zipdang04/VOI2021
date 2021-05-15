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

#define MAX 300001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n;
char c[MAX];
vi graph[MAX];
int ways[MAX][8];

void dfs(int node, int parent){
	int currColor = c[node];
	int currAns[8] = {};
	for (int child: graph[node]){
		if (child == parent) continue;
		dfs(child, node);
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//read data
	cin >> n >> c + 1;
	FOR(int, i, 1, n)
		if (c[i] == 'D') c[i] = 0;
		else if (c[i] == 'X') c[i] = 1;
		else if (c[i] == 'L') c[i] = 2;
		else c[i] = 3;
	for (int i = 1; i < n; i++)
	{
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	//=========================
	//debug
	FOR(int, i,1, n) cerr << int(c[i]) << ' ';cerr  << '\n';
	//=========================
	dfs(1, 1);


	FOR(int, i, 1, n){cerr << i << ": ";FOR(int, j, 0, 7) cerr << bitset<3>(j) << '/' << ways[i][j] << ' '; cerr << '\n';}
	int ans = 0;
	FOR(int, i, 0, 6) ans += ways[1][i];
	cout << ans;
}