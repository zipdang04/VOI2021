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

#define MAX 10000001
const ll MOD = 1 << 30;

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

ll a, b, c;
//==========================================================================
void sub1(){
	ll answer = 0;
	FOR(ll, x, 1, a)
		FOR(ll, y, 1, b)
			FOR(ll, z, 1, c){
				ll prod = x * y * z;
				ll cnt = 0;
				FOR(ll, i, 1, prod)
					if (prod % i == 0) cnt++;
				answer += cnt;
				answer %= MOD;
			}
	cout << answer;
}
//==========================================================================

ll pr[MAX];
void initPrime(){
	FOR(int, i, 2, MAX - 1){
		if (pr[i]) continue;
		pr[i] = i;

		for (ll j = ll(i) * i; j < MAX; j += i)
			if (!pr[j]) pr[j] = i;
	}
}

ll cntDiv(ll num){
	ll ans = 1;
	ll p = 0, d = 0;
	while (num > 1){
		ll currP = pr[num]; num /= currP;
		if (currP != p)
			ans *= d + 1, 
			p = currP, d = 1;
		else d++;
	}
	ans *= d + 1;
	return ans;
}
void sub2(){
	initPrime();
	ll ans = 0;
	FOR(ll, x, 1, a)
		FOR(ll, y, 1, b)
			FOR(ll, z, 1, c){
				ll prod = x * y * z;
				ans += cntDiv(prod);
				ans %= MOD;
			}
	cout << ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> a >> b >> c;
	ll thresSub = max(a, max(b, c));
	// sub1(); sub2(); return 0;
	if (thresSub <= 20) sub1();
	else if (thresSub <= 200) sub2();
	else if (thresSub <= 2000) cout << "em yeu anh Hanh";
	else cout << "anh Hanh iu em khong :P";
}