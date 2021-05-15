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

const ll oo = -1;

ll m, n, k, x, y, t;
ll **f[5001];
ll s[5001][5001];
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n >> x >> y >> t; k = m * n;
	FOR(ll, i, 1, m)
		FOR(ll, j, 1, n)
			cin >> s[i][j];
	FOR(ll, ti, 0, k){
		f[ti] = new ll*[m + 1];
		FOR(ll, row, 1, m)
			f[ti][row] = new ll[n + 1];
	}
	FOR(ll, p, 0, k)
		FOR(ll, q, 1, m)
			FOR(ll, r, 1, n)
				f[p][q][r] = oo;
	
	f[0][x][y] = s[x][y];
	FOR(ll, ti, 1, k){
		FOR(ll, row, 1, m){
			FOR(ll, col, 1, n){
				ll value = f[ti - 1][row][col];
				if (row > 1 && f[ti - 1][row - 1][col] != oo)
					value = max(value, f[ti - 1][row - 1][col] + s[row][col]);
				if (row < m && f[ti - 1][row + 1][col] != oo)
					value = max(value, f[ti - 1][row + 1][col] + s[row][col]);
				if (col > 1 && f[ti - 1][row][col - 1] != oo)
					value = max(value, f[ti - 1][row][col - 1] + s[row][col]);
				if (col < n && f[ti - 1][row][col + 1] != oo)
					value = max(value, f[ti - 1][row][col + 1] + s[row][col]);
				f[ti][row][col] = value;
				// cerr << value << ' ';
			}
			// cerr << '\n';
		}
		// cerr << '\n';
	}
	// cerr << "////";
	ll answer = 0;
	FOR(ll, row, 1, m)
		FOR(ll, col, 1, n){
			ll bestMushroom = 0;
			if (row > 1) bestMushroom = max(bestMushroom, s[row - 1][col]);
			if (row < m) bestMushroom = max(bestMushroom, s[row + 1][col]);
			if (col > 1) bestMushroom = max(bestMushroom, s[row][col - 1]);
			if (col < n) bestMushroom = max(bestMushroom, s[row][col + 1]);
			FOR(ll, ti, 1, min(t, k)){
				// cerr << ti << ' ' << row << ' ' << col << '\n';
				ll remain = t - ti;
				if (f[ti][row][col] != oo)
					answer = max(answer, f[ti][row][col] + (remain / 2) * (s[row][col] + bestMushroom) + (remain & 1) * bestMushroom);
				// cerr << "done\n";
			}
		}
	cout << answer;
}