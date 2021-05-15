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

int n, q;
int a[MAX];
struct SegTree{
	int len;
	int it[MAX * 4] = {};
	bool isOn[MAX] = {};

	void turnOn(int index, int left, int right, int pos){
		if (left == right){
			it[index] = pos; isOn[pos] = true;
			return;
		}

		int y = index << 1, mid = (left + right) >> 1;
		if (left <= pos && pos <= mid) turnOn(y, left, mid, pos);
		else turnOn(y + 1, mid + 1, right, pos);

		it[index] = max(it[y], it[y + 1]);
	}
	
	void turnOff(int index, int left, int right, int pos){
		if (left == right){
			it[index] = 0; return;
		}

		int y = index << 1, mid = (left + right) >> 1;
		if (left <= pos && pos <= mid) turnOff(y, left, mid, pos);
		else turnOff(y + 1, mid + 1, right, pos);

		it[index] = max(it[y], it[y + 1]);
	}

	int getMax(int index, int left, int right, int pos){
		if (left > pos) return 0;
		if (right <= pos) return it[index];

		int y = index << 1, mid = (left + right) >> 1;
		return max(getMax(y, left, mid, pos), getMax(y + 1, mid + 1, right, pos));
	}

	// we will use this
	void init(int _len){len = _len;}
	void turnOn(int _pos){turnOn(1, 1, len, _pos);}
	void turnOff(int _pos){turnOff(1, 1, len, _pos);}
	int getMax(int _pos){return getMax(1, 1, len, _pos);}
} segTree;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q; segTree.init(n);
	FOR(int, i, 1, n) cin >> a[i];

	segTree.turnOn(1);
	FOR(int, i, 2, n)
		if (a[i] % a[i - 1]) segTree.turnOn(i);

	FOR(int, _, 1, q){
		int que, pos; cin >> que >> pos;
		if (que == 1){
			bool isOn = segTree.isOn[pos];
			int currPart = segTree.getMax(pos);

			int val; cin >> val;
			a[pos] = val;
			if (pos != 1){
				if (a[pos] % a[pos - 1]) segTree.turnOn(pos);
				else segTree.turnOff(pos);
			}
			if (pos != n){
				if (a[pos + 1] % a[pos]) segTree.turnOn(pos + 1);
				else segTree.turnOff(pos + 1);
			}
		} else {
			cout << segTree.getMax(pos) << '\n';
		}
	}
}