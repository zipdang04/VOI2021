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

#define MAX 32
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

int m, n;
int board[MAX][MAX];
int ans[MAX * 2];
vi graph[MAX * 2];

#define row(r) (r)
#define col(c) (c + m)
#define rev(color) (3 - (color))

bool dfs(int node, int color){
	for (int child: graph[node]){
		if (ans[child]){
			if (ans[child] == color) return false;
			continue;
		} else {
			ans[child] = rev(color);
			dfs(child, rev(color));
		}
	}
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	FOR(int, i, 1, m)
		FOR(int, j, 1, n){
			cin >> board[i][j];
		}
	
	FOR(int, r, 1, m)
		FOR(int, c, 1, n){
			int val = board[r][c];
			if (val == 1 || val == 2){
				if (ans[row(r)] && ans[row(r)] != val){cout << 0; return 0;}
				if (ans[col(c)] && ans[col(c)] != val){cout << 0; return 0;}
				ans[row(r)] = ans[col(c)] = val;
			} else if (val == 3){
				graph[row(r)].push_back(col(c));
				graph[col(c)].push_back(row(r));
			}
		}

	bool nothing = true;
	FOR(int, pos, 1, m + n){
		if (ans[pos]){
			nothing = false;
			if (!dfs(pos, ans[pos])){cout << 0; return 0;}
		}
	}

	int group = 0;
	FOR(int, pos, 1, m + n){
		if (!ans[pos]) {group++; ans[pos] = 1; dfs(pos, 1);}
	}
	ll ans = 1ll << group;
	if (nothing) ans--;
	cout << ans;
}