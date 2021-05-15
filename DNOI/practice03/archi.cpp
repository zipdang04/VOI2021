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

#define MAX 2005
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

struct Point{int x, y;};
struct Line{Point one, two;};

int n;
Point point[MAX];
vi graph[MAX * MAX];
bool visited[MAX * MAX];
#define hash(x, y) ((x) * 2001 + (y))

int dfs(int node){
	if (visited[node]) return 0;
	visited[node] = true;
	int ans = int(graph[node].size()) % 2;
	for (int child: graph[node]){
		ans += dfs(child);
	}
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, _, 1, n){
		int x, y, u, v; cin >> x >> y >> u >> v;
		if (x > u) swap(x, u);
		if (y > v) swap(y, v);
		x += 1000, y += 1000, u += 1000, v += 1000;

		if (x == u)
			FOR(int, i, y, v - 1){
				int n1 = hash(x, i), n2 = hash(x, i + 1);
				graph[n1].push_back(n2);
				graph[n2].push_back(n1);
			}
		else
			FOR(int, i, x, u - 1){
				int n1 = hash(i, y), n2 = hash(i + 1, y);
				graph[n1].push_back(n2);
				graph[n2].push_back(n1);
			}
	}
	int ans = 0;
	FOR(int, i, 0, MAX * MAX - 1){
		if (!graph[i].size()) continue;
		if (visited[i]) continue;
		int curr = dfs(i);
		if (curr == 0) ans++;
		else ans += (curr >> 1) + (curr & 1);
	}
	cout << ans;
}