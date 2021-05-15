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

int n;
bool black[MAX];
vi graph[MAX];
int sz[MAX];

int dfs(int node, int parent){
	int best = n, worst = n;
	for (int child: graph[node]){
		if (child == parent) continue;
		int place = dfs(child, node), currSize = sz[child];

		best = min(best, place),
		worst = min(worst, currSize - place + 1);
		sz[node] += currSize;
	}
	
	if (!sz[node]){
		sz[node] = 1;
		return 1;
	}
	
	if (!black[node])
		return best;
	else 
		return sz[node] - worst + 1;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n) cin >> black[i];
	FOR(int, i, 2, n){
		int par; cin >> par;
		graph[par].push_back(i);
	}
	int ans = dfs(1, 1);
	cout << sz[1] - ans + 1;
}