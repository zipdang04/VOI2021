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

ll m, n, k;
ll marble[3][MAX];
bool flip = false;

ll sum = 0;

ll process(ll *arr, ll threshold){
	ll currSum = 0;
	FOR(ll, i, 1, n) currSum += arr[i];
	if (currSum % n || currSum / n != threshold) return -1;

	ll pos = 1, ans = 0;
	FOR(ll, i, 1, n){
		if (arr[i] >= threshold) continue;
		while (arr[i] < threshold){
			while (arr[pos] <= threshold) pos++;
			ll need = threshold - arr[i], remain = arr[pos] - threshold;

			ll choose = min(need, remain);
			ans += choose * abs(i - pos), arr[i] += choose, arr[pos] -= choose;
		}
	}
	return ans;
}

bool check(ll *arr){
	FOR(ll, i, 2, n)
		if (arr[i] != arr[i - 1]) return false;
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n >> k;
	if (m > 2 && n > 2){
		cout << -1; return 0;
	}
	if (m > n) {flip = true; swap(m, n);}

	FOR(ll, _, 1, k){
		ll row, col, val; cin >> row >> col >> val;
		
		sum += val;
		if (flip) swap(row, col);
		marble[row][col] += val;
	}
	if (sum % (m * n)){cout << -1; return 0;}
	ll threshold = sum / (m * n);


	//m = 1
	if (m == 1){
		if (check(marble[1])) cout << 0;
		else cout << -1;
		return 0;
	}

	// m = 2
	FOR(ll, i, 1, n)
		if (i & 1) swap(marble[1][i], marble[2][i]);
	ll x1 = process(marble[1], threshold), x2 = process(marble[2], threshold);
	if (x1 == -1 || x2 == -1) {cout << -1; return 0;}
	cout << x1 + x2 << '\n';
}