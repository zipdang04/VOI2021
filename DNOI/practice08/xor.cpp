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

struct Node{
	int pos = -1;
	Node *child[2] = {};
};

int n;
Node *root;
int a[MAX];

void add(int num, int pos){
	Node *curr = root;
	FORR(int, bit, 30, 0){
		bool state = testBit(num, bit);
		if (curr -> child[state] == nullptr)
			curr -> child[state] = new Node;
		curr = curr -> child[state];
	}
	curr -> pos = pos;
}

int dfs(Node *node, int lvl, int num){
	if (lvl == 0) return node -> pos;
	
	lvl--;
	bool state = testBit(num, lvl);

	if (node -> child[!state] != nullptr)
		return dfs(node -> child[!state], lvl, num);
	else
		return dfs(node -> child[state], lvl, num);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> n;
		FOR(int, i, 1, n) {cin >> a[i];}
		
		root = new Node; add(a[0], 0);
		int ans = 0;
		FOR(int, i, 1, n){
			ans = max(ans, a[i] ^ a[dfs(root, 31, a[i])]);
			add(a[i], i);
		}
		cout << ans << '\n';
		delete root;
	}
}