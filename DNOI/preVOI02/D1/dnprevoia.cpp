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
const ll NaN = -1;

ll n;

ll mul(ll x1, ll x2){
	if (x1 == NaN || x2 == NaN) return NaN;
	if (x1 <= n / x2) return x1 * x2;
	else return NaN;
}

ll power(ll a, ll p){
	if (p == 0) return 1;
	ll ans = power(a, p >> 1);
	ans = mul(ans, ans);
	if (p & 1) ans = mul(ans, a);
	return ans;
}

ll bs(ll pw){
	ll left = 1, right = 1000000000;
	while (left <= right){
		ll mid = (left + right) >> 1;
		ll num = power(mid, pw);

		if (num == n) return mid;
		else if (num == NaN) right = mid - 1;
		else left = mid + 1;
	}
	return NaN;
}

void add(vector<pll> &v, ll num, ll pw, bool isOdd){
	if (isOdd){
		if (pw & 1)
			v.push_back({-num, pw});
	} else {
		v.push_back({num, pw});
		if (!(pw & 1))
			v.push_back({-num, pw});
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> n; bool isOdd = false;
		if (n < 0) isOdd = true, n = -n;
		vector<pll> v;
		add(v, n, 1, isOdd);
		FOR(ll, pw, 2, 18){
			ll num = bs(pw);
			if (num != NaN)
				add(v, num, pw, isOdd);
		}
		FOR(ll, num, 2, 10){
			ll pw = 0, prod = 1;
			while (prod != NaN) {
				if (prod == n)
					add(v, num, pw, isOdd);
				prod = mul(prod, num);
				pw++;
			}
		}

		sort(v.begin(), v.end());
		pll prev = {0, 0};
		for (pll i: v){
			if (i != prev)
				cout << i.fi << ' ' << i.se << '\n';
			prev = i;
		}
		cout << '\n';
	}
}