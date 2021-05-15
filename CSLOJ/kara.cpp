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

struct Node{
	int lvl = 0, cnt[2] = {};
	int child[26] = {};
	Node(){
		lvl = cnt[0] = cnt[1] = 0;
		FOR(int, i, 0, 25) child[i] = -1;
	}
};

Node trie[MAX]; int len = 0;
const int root = 0;
void add(string s, int type){
	int node = root;
	trie[node].cnt[type]++;

	int lvl = 0;
	for (char c: s){
		int pos = c - 'a';
		if (trie[node].child[pos] == -1)
			trie[node].child[pos] = ++len;
		node = trie[node].child[pos];
		trie[node].lvl = ++lvl;
		trie[node].cnt[type]++;
	}
}

int f[MAX];

int dp(int node){
	if (f[node] != -1) return f[node];
	Node curr = trie[node];
	int turn = curr.lvl & 1;
	
	f[node] = 0;
	if (!curr.cnt[turn]) return 0;

	FOR(int, choice, 0, 25){
		int childPos = curr.child[choice];
		if (childPos == -1) continue;
		Node child = trie[childPos];
		
		if (dp(childPos) == 0) f[node] = 1;
	}
	return f[node];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(int, i, 1, n) {string s; cin >> s; add(s, 0);}
	cin >> m; FOR(int, i, 1, m) {string s; cin >> s; add(s, 1);}

	FOR(int, i, 0, len) f[i] = -1;
	cout << (dp(root) ? "Nina" : "Emilija");
}																					