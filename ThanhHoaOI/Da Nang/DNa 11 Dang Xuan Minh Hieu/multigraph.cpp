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

#define MAX 100001
#define MOD 999999937

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

class SegTree{
	private:
		int len;
		int it[MAX * 4];

		void update(int ind, int left, int right, int pos, int val){
			if (left == right){
				it[ind] = val;
				return;
			}

			int y = ind << 1, mid = (left + right) >> 1;
			if (pos <= mid) update(y, left, mid, pos, val);
			else update(y + 1, mid + 1, right, pos, val);

			it[ind] = min(it[y], it[y + 1]);
		}

		int get(int ind, int left, int right, int posL, int posR){
			if (right < posL || posR < left) return INT32_MAX;
			if (posL <= left && right <= posR) return it[ind];
			
			int y = ind << 1, mid = (left + right) >> 1;
			return min(
				get(y, left, mid, posL, posR),
				get(y + 1, mid + 1, right, posL, posR)
			);
		}
	public:
		SegTree(int len): len(len){
			FOR(int, i, 1, 4 * len) it[i] = INT32_MAX;
		}
		
		void update(int pos, int val) {update(1, 1, len, pos, val);}
		int get(int posL, int posR) {
			if (posR < posL) return INT32_MAX;
			return get(1, 1, len, posL, posR);
		}
} *segTree;

int n, q;
int a[MAX];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("multigraph.inp", "r", stdin);
	freopen("multigraph.out", "w", stdout);
	cin >> n >> q; FOR(int, i, 1, n) cin >> a[i];
	segTree = new SegTree(n);
	FOR(int, i, 1, n) segTree -> update(i, a[i]);

	FOR(int, _, 1, q){
		int type, u, v; cin >> type >> u >> v;

		if (type == 1){
			a[u] = v;
			segTree -> update(u, v);
		} else {
			if (u == v) {cout << "0\n"; continue;}
			
			ll way1 = 1ll * a[u] * a[v];
			ll way2 = 1ll * min(segTree -> get(1, u - 1), min(segTree -> get(u + 1, v - 1), segTree -> get(v + 1, n))) * (a[u] + a[v]);
			
			cout << min(way1, way2) << '\n';
		}
	}
}