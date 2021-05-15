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

ll n, k;
ll a[MAX];
class SegTree{
	private:
		ll it[MAX];
		void buildTree(ll ind, ll left, ll right){
			if (left == right){it[ind] = a[left]; return;}
			ll y = ind << 1, mid = (left + right) >> 1;
			buildTree(y, left, mid);
			buildTree(y + 1, mid + 1, right);
			it[ind] = __gcd(it[y], it[y + 1]);
		}
		ll get(ll ind, ll left, ll right, ll posL, ll posR){
			if (right < posL || posR < left) return 0;
			if (posL <= left && right <= posR) return it[ind];
			ll y = ind << 1, mid = (left + right) >> 1;
			return __gcd(get(y, left, mid, posL, posR), get(y + 1, mid + 1, right, posL, posR));
		}
	public:
		void init(){buildTree(1, 1, n);}
		ll get(ll _posL, ll _posR){return get(1, 1, n, _posL, _posR);}
} segTree;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
#ifndef ONLINE_JUDGE
	freopen("vz37_gcd.inp", "r", stdin);
	freopen("vz37_gcd.out", "w", stdout);
#endif

	cin >> n >> k;
	FOR(ll, i, 1, n) cin >> a[i];
	segTree.init();
	ll ma = 0;
	FOR(ll, i, 1, n - k + 1){
		ma = max(ma, segTree.get(i, i + k - 1));
	}
	cout << ma << '\n';
}