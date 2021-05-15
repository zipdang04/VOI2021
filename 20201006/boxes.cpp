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

#define MAX 22
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

int n, k;
int c[MAX][MAX];
int f[1 << 20];


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("boxes.inp", "r", stdin);
	freopen("boxes.out", "w", stdout);
	cin >> n >> k;
	FOR(int, i, 0, n - 1)
		FOR(int, j, 0, n - 1) cin >> c[i][j];
	FOR(int, i, 0, (1 << n) - 1){
		if (cntBit(i) <= k) continue;
		int state = i; f[state] = INT32_MAX;

		int on[20] = {}, size = 0;
		FOR(int, bit, 0, n - 1)
			if (testBit(state, bit)) on[size++] = bit;
		FOR(int, ii, 0, size - 1){
			int off = on[ii];
			FOR(int, jj, 0, size - 1){
				if (ii == jj) continue;
				int box = on[jj];
				f[state] = min(f[state], c[off][box] + f[flipBit(state, off)]);
			}
		}
	}
	cout << f[(1 << n) - 1];
}