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

int n, m;
int c[MAX];
vi graph[MAX];
int root[MAX];
int cnt[MAX];

void dfs(int node, int num){
	root[node] = num; cnt[num]++;
	int currColor = c[node];
	for (int child: graph[node]){
		if (root[child]) continue;
		if (c[child] != currColor) continue;
		dfs(child, num);
	}
}

void clear(){
	FOR(int, i, 1, n){
		c[i] = 0;
		graph[i].clear();
		root[i] = 0;
		cnt[i] = 0;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> n >> m;
		FOR(int, i, 1, n) cin >> c[i];
		FOR(int, _, 1, m){
			int u, v; cin >> u >> v;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		FOR(int, i, 1, n)
			if (!root[i]) dfs(i, i);
		
		int ans = 0;
		FOR(int, node, 1, n){
			int currRoot = root[node];
			ans = max(ans, cnt[currRoot]);

			mii saveValue;
			for (int child: graph[node]){
				int childRoot = root[child];
				if (childRoot == currRoot) continue;
				saveValue[childRoot] = cnt[childRoot];
			}

			mii total;
			for (pii i: saveValue)
				total[c[i.fi]] += i.se;

			for (pii i: total)
				ans = max(ans, i.se + 1);
		}
		cout << ans << '\n';
		clear();
	}
}