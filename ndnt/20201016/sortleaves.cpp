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

struct Node{
	int posL = 0, posR = 0;
	bool isLeaf = false;
	pii range = {0, 0};
};

int n;
Node tree[MAX];
bool okay = true;

void dfs(int nodeIndex){
	Node &currNode = tree[nodeIndex];
	
	if (currNode.isLeaf) return;
	dfs(currNode.posL), dfs(currNode.posR);
	Node &nLeft = tree[currNode.posL], &nRight = tree[currNode.posR];
	
	currNode.range = {min(nLeft.range.fi, nRight.range.fi), max(nLeft.range.se, nRight.range.se)};
	if (nLeft.range.fi > nRight.range.fi)
		swap(nLeft, nRight);
	if (nLeft.range.se > nRight.range.fi)
		okay = false;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> n;
		FOR(int, i, 1, n){
			int l, r; cin >> l >> r;
			if (l == -1){
				tree[i].posL = tree[i].posR = 0;
				tree[i].isLeaf = true;
				tree[i].range = {r, r};
			} else {
				tree[i].posL = l; tree[i].posR = r;
				tree[i].isLeaf = false;
			}
		}
		dfs(1);
		cout << (okay ? 1 : -1) << '\n';
		okay = true;
	}
}