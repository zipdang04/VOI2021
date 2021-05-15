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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const int oo = -1;

int n, k;
vi graph[MAX];
int f[301][301];
int depth;

void dp(int node, int parent){
	f[node][0] = 1;
	for (int child: graph[node]){
		if (child == parent) continue;
		dp(child, node);
	}

	FOR(int, childDepth, 0, depth - 1){
		if (childDepth == 0){
			int getDepth = max(0, depth - 1 - childDepth);
			for (int child: graph[node])
				f[node][childDepth] += f[child][getDepth];
		} else {
			for (int c1: graph[node]){
				if (c1 == parent) continue;
				
				int curr = f[c1][childDepth - 1];
				int getDepth = max(childDepth - 1, depth - 1 - childDepth);
				for (int c2: graph[node]){
					if (c2 == parent) continue;
					if (c2 == c1) continue;
					
					curr += f[c2][getDepth];
				}

				f[node][childDepth] = max(f[node][childDepth], curr);
			}
		}
	}
	FORR(int, childDepth, depth - 1, 1)
		f[node][childDepth - 1] = max(f[node][childDepth - 1], f[node][childDepth]);
}

bool check(int d){
	depth = d;
	FOR(int, node, 1, n)
		FOR(int, dep, 1, n)
			f[node][dep] = 0;
	dp(1, 1);
	return f[1][0] >= k;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n >> k;
	for (int i = 1; i < n; i++)
	{
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	//=========================
	int l = 2, r = n, ans = 1;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check(mid))
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	}
	cout << ans;
}