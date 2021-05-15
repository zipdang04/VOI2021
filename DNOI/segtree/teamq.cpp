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

#define MAX 200001
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

pair<int, pii> cont[MAX];
int n;
int bit[MAX];

void update(int ind, int val){
	while (ind <= n)
		bit[ind] = min(bit[ind], val), ind += ind & -ind;
}

int get(int ind){
	int ans = n + 1;
	while (ind)
		ans = min(ans, bit[ind]), ind -= ind & -ind;
	return ans;
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n) {int num; cin >> num; cont[num].fi = i;}
	FOR(int, i, 1, n) {int num; cin >> num; cont[num].se.fi = i;}
	FOR(int, i, 1, n) {int num; cin >> num; cont[num].se.se = i;}
	sort(cont + 1, cont + 1 + n);
	FOR(int, i, 1, n) bit[i] = n + 5;
	int ans = 0;
	FOR(int, i, 1, n){
		pii curr = cont[i].se;
		if (get(curr.fi) >= curr.se) {ans++;}
		update(curr.fi, curr.se);
	}
	cout << ans;
}