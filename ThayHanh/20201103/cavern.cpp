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

#define MAX 5005
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

int n, m;
int a[MAX], b[MAX];
deque<int> dqA, dqB;

void add(int pos, int limit, int *arr, deque<int> &dq){
	int num = arr[pos];
	while (!dq.empty() && arr[dq.front()] < num) dq.pop_front();
	
	dq.push_front(pos);
	if (pos - dq.back() > limit) dq.pop_back();
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef ONLINE_JUDGE
	freopen("cavern.inp", "r", stdin);
	freopen("cavern.out", "w", stdout);
	#endif
	
	cin >> n >> m;
	FOR(int, i, 1, m) cin >> a[i];
	FOR(int, i, 1, m) cin >> b[i];

	ll answer = 0;
	FOR(int, len, 1, m){
		FOR(int, i, 1, len) add(i, len, a, dqA), add(i, len, b, dqB);

		int maxi = 1e9;
		FOR(int, col, len + 1, m + 1){
			add(col, len, a, dqA), add(col, len, b, dqB);
			int maxA = a[dqA.back()], maxB = b[dqB.back()];
			maxi = min(maxi, max(0, n - maxA - maxB));
		}
		answer = max(answer, ll(maxi) * len);
		dqA.clear(), dqB.clear();
	}
	cout << answer;
}