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

#define MAX 1001
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

int m, n;
int a[MAX][MAX];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	FOR(int, i,1 , m)
		FOR(int, j, 1, n)
			cin >> a[i][j];
	int ans = 0;
	FOR(int, i, 1, m / 2){
		FOR(int, j, 1, n / 2){
			int v[4] = {};
			v[0] = a[i][j];
			v[1] = a[i][n - j + 1];
			v[2] = a[m - i + 1][j];
			v[3] = a[m - i + 1][n - j + 1];

			FOR(int, i, 0, 2)
				FOR(int, j, i + 1, 3)
					if (v[i] > v[j]) swap(v[i], v[j]);
			
			int d = 1, ma = 1;
			FOR(int, i, 1, 3)
				if (v[i] == v[i - 1]){
					d++; ma = max(ma, d);
				} else d = 1;
			ans += 4 - ma;
		} 
	}
	if (m & 1){
		int midRow = m / 2 + 1;
		FOR(int, j, 1, n / 2){
			ans += a[midRow][j] != a[midRow][n - j + 1];
		}
	}
	if (n & 1){
		int midCol = n / 2 + 1;
		FOR(int, i, 1, m / 2){
			ans += a[i][midCol] != a[m - i + 1][midCol];
		}
	}
	cout << ans;
}