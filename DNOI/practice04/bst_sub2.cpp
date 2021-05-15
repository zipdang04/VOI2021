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

#define MAX 2000001
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

map<int, int> bst;
int n, h;

void calculate(int nodePos, int rangeL, int rangeR, int height){
	if (rangeL > rangeR) return;
	if (rangeL == rangeR){
		bst[nodePos] = rangeL;
		return;
	}

	int maxChildSize = (1 << (height - 1)) - 1;
	int posL = nodePos << 1, posR = posL + 1;
	FOR(int, root, rangeL, rangeR){
		int sizeR = rangeR - root;
		if (sizeR > maxChildSize) continue;

		bst[nodePos] = root;
		calculate(posL, rangeL, root - 1, height - 1);
		calculate(posR, root + 1, rangeR, height - 1);
		break;
	}
}

int currTime = 0;
int timeAdd[MAX];
void dfs(int nodePos){
	int value = bst[nodePos];
	if (!value) return;
	timeAdd[++currTime] = value;
	int posL = nodePos << 1, posR = posL + 1;
	dfs(posL); dfs(posR);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> h;

	//base cases
	if ((1 << h) - 1 < n){cout << -1; return 0;}
	//========================= 
	//main
	calculate(1, 1, n, h);
	dfs(1);
	//=========================
	FOR(int, i, 1, n) cout << timeAdd[i] << ' ';
}