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
mii bst;
int height = 0;

void insert(int num){
	int pos = 1;
	while (true){
		int currVal = bst[pos];
		if (currVal == 0){
			bst[pos] = num;
			break;
		} 
		else{
			pos <<= 1;
			if (num > currVal) pos++;
		} 
	}
}

void dfs(int nodePos, int level){
	int value = bst[nodePos];
	if (!value) return;
	height = max(height, level);

	int posL = nodePos << 1, posR = posL + 1;
	dfs(posL, level + 1); dfs(posR, level + 1);
}

int n, h;
int a[MAX];
int arr[MAX];
bool visited[MAX];
bool done = false;

void dqql(int pos){
	if (pos > n){
		FOR(int, i, 1, n) insert(arr[i]);
		dfs(1, 1);
		if (height <= h){
			done = true;
			FOR(int, i, 1, n) cout << arr[i] << ' ';
		}
		bst.clear(); height = 0;
		return;
	}
	FOR(int, i, 1, n)
		if (!visited[i]){
			visited[i] = true; arr[pos] = i;
			dqql(pos + 1);
			visited[i] = false;
			if (done) return;
		}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> h; FOR(int, i, 1, n) a[i] = i;
	dqql(1);
	if (!done) cout << -1;
}