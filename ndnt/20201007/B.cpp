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
const ll MAXVAL = 2000000003;
const ll ADD = 1000000001;

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

class SegTree{
	private:
		umll it[MAX * 4];
		ll len = 0;

		void insert(umll &bit, ll num){
			num += ADD;

			while (num < MAXVAL)
				bit[num]++, num += num & -num;
		}

		ll get(umll &bit, ll num){
			num += ADD;

			ll ans = 0;
			while (num)
				ans += bit[num], num -= num & -num;
			return ans;
		}

		void update(ll index, ll left, ll right, ll pos, ll value){
			insert(it[index], value);
			if (left == right) return;

			ll y = index << 1, mid = (left + right)  >> 1;
			if (left <= pos && pos <= mid) update(y, left, mid, pos, value);
			else update(y + 1, mid + 1, right, pos, value);
		}

		ll getAns(ll index, ll left, ll right, ll posL, ll posR, ll value){
			if (right < posL || posR < left) return 0;
			if (posL <= left && right <= posR) return get(it[index], value);

			ll y = index << 1, mid = (left + right)  >> 1;
			return getAns(y, left, mid, posL, posR, value)
				+ getAns(y + 1, mid + 1, right, posL, posR, value);
		}
	public:
		SegTree(ll _len){
			len = _len;
		}

		void update(ll _pos, ll _value){
			update(1, 1, len, _pos, _value);
		}

		ll getAns(ll _left, ll _right, ll _value){
			return getAns(1, 1, len, _left, _right, _value);
		}
};

ll n, a[MAX];

// SegTree seg;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n; 
	FOR(ll, i, 1, n) cin >> a[i];
	//=========================
	//init
	SegTree seg(n);
	FOR(ll, i, 1, n)
		seg.update(i, a[i]);
	//=========================
	//queries
	ll q; cin >> q;
	FOR(ll, _, 1, q){
		ll l, r, k; cin >> l >> r >> k;
		ll left = -1000000000, right = 1000000000, ans = right;
		while (left <= right){
			ll mid = (left + right) / 2;
			if (seg.getAns(l, r, mid) >= k)
				ans = mid, right = mid - 1;
			else
				left = mid + 1;
		}
		cout << ans << '\n';
	}
	//=========================
	
}