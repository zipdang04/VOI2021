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

ll n, k;
ll a[MAX];

ll amount(ll num){
	return (num * (num + 1) / 2) - (a[n] * (num / n) + a[num % n]);
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("nhanpham.inp", "r", stdin);
	freopen("nhanpham.out", "w", stdout);
	// #endif

	cin >> n >> k;
	FOR(ll, i, 1, n) cin >> a[i];
	
	if (n == 1 && k == 0){
		cout << a[1] * 2 - 1;
		return 0;
	} else {
		bool sub3 = true;
		FOR(ll, i, 1, n)
			if (a[i] > 1000000){
				sub3 = false;
				break;
			}
		
		FOR(ll, i, 1, n) a[i] += a[i - 1];
		if (sub3)
			FOR(ll, i, 1, 1000000)
				if (amount(i) >= k){
					cout << i; return 0;
				}
				
		ll left = 1, right = 2100000000, ans = 0;
		while (left <= right){
			ll mid = (left + right) >> 1;
			if (amount(mid) >= k)
				ans = mid, right = mid - 1;
			else
				left = mid + 1;
		}
		cout << ans << '\n';
	}

}