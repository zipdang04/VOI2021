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

#define MAX 500005
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

bool isSub1 = false;
ll n, q;
ll a[MAX];
//===========================================
ll sub1(ll start, ll end){
	ll curr = 0, cnt = 0;
	FOR(ll, i, start, end){
		ll num = a[i];
		if (curr < num)
			curr = num, cnt++;
	}
	return cnt;
}
//===========================================

const ll BIT = 18;
ll jump[MAX];
ll rmq[BIT + 1][MAX];

stack<int> st;
void initJump(){
	a[0] = a[n + 1] = INT64_MAX;

	st.push(n + 1);
	FORR(int, i, n, 1){
		ll num = a[i];
		while (a[st.top()] < num) st.pop();
		jump[i] = st.top(); st.push(i);
	}
	// // FOR(int, i, 1, n) cerr << jump[i] << ' '; cerr << '\n';
}
void initRMQ(){
	FOR(ll, bit, 0, BIT)
		rmq[bit][n + 1] = n + 1;
	FOR(ll, bit, 0, BIT)
		if (bit == 0)
			FOR(ll, i, 1, n)
				rmq[bit][i] = jump[i];
		else
			FOR(ll, i, 1, n)
				rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}

ll letsgo(ll node, ll dist){
	FOR(ll, bit, 0, BIT){
		if (testBit(dist, bit))
			node = rmq[bit][node];
	}
	if (node == 0) node = n + 1;
	return node;
}

ll sub2(ll start, ll end){
	ll ans = 0;
	FORR(ll, bit, BIT, 0){
		if (rmq[bit][start] > end) continue;
		start = rmq[bit][start], ans = flipBit(ans, bit);
	}
	return ans + 1; 
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n >> q; if (n <= 5000 && q <= 5000) isSub1 = true;
	FOR(ll, i, 1, n) cin >> a[i];
	//=========================
	initJump(); initRMQ();
	FOR(ll, _, 1, q){
		ll l, r; cin >> l >> r;
		cout << sub2(l, r) << '\n';
	} 
}