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

#define MAX 301
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

const int MAX_VAL = 50000001;

int n;
int a[MAX];
int ans[MAX];

int checkSize(int person, int size){
	int left = 1, right = MAX_VAL, ans = 0, bestSize = -1;
	while (left <= right){
		int mid = (left + right) >> 1;

		int currGroup = a[person] / mid;
		int currSize = 1;
		FOR(int, i, person + 1, n)
			if (a[i] / mid == currGroup) currSize++;
			else break;
		FORR(int, i, person - 1, 1)
			if (a[i] / mid == currGroup) currSize++;
			else break;
		
		if (currSize >= size)
			bestSize = currSize, ans = mid, right = mid - 1;
		else
			left = mid + 1;
	}

	if (bestSize != size) ans = 0;
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
	sort(a + 1, a +  1 + n);
	FOR(int, i, 1, n) ans[i] = INT32_MAX;

	FOR(int, i, 1, n){
		FOR(int, teamSize, 1, n){
			int days = checkSize(i, teamSize);
			if (!days) continue;
			ans[teamSize] = min(ans[teamSize], days);
		}
	}
	
	FOR(int, i, 1, n) if (ans[i] == INT32_MAX) cout << -1 << '\n'; else cout << ans[i] << '\n';
}