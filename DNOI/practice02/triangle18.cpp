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

#define MAX 3000001
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

ll n, q;
unordered_map<ll, multiset<ll>> row, col;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	FOR(ll, i, 1, n){
		ll x, y; cin >> x >> y;
		row[x].insert(y);
		col[y].insert(x);
	}
	FOR(ll, _, 1, q){
		ll type, x, y; cin >> type >> x >> y;
		if (type == 1){
			row[x].insert(y);
			col[y].insert(x);
		} else if (type == 2){
			row[x].erase(row[x].find(y));
			col[y].erase(col[y].find(x));
		} else {
			if (row[x].empty()) {cout << 0 << '\n'; continue;}
			if (col[y].empty()) {cout << 0 << '\n'; continue;}

			ll smallX = *col[y].begin();
			ll bigX = *col[y].rbegin();

			ll smallY = *row[x].begin();
			ll bigY = *row[x].rbegin();

			ll lenX = max(abs(x - smallX), abs(x - bigX));
			ll lenY = max(abs(y - smallY), abs(y - bigY));

			ll area = lenX * lenY;
			bool odd = area & 1; area >>= 1;
			cout << area;
			if (odd) cout << ".5";
			cout << '\n';
		}
	}
}