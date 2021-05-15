#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 505
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

struct Point{ll x, y;};
Point point[100001][7];
ll n, k, p, r;
ll a[MAX][MAX];

ll sub1(){
	ll answer = 0;
	FOR(ll, _, 1, k){
		ll mark[MAX][MAX] = {};
		FOR(ll, i, 1, p){
			ll x1 = point[_][i].x, y1 = point[_][i].y;
			mark[x1][y1] += 1;
			mark[x1][y1 + r] += -1;
			mark[x1 + r][y1] += -1;
			mark[x1 + r][y1 + r] += 1;
		}
		ll sum = 0;
		FOR(ll, i, 1, n)
			FOR(ll, j, 1, n){
				mark[i][j] += mark[i - 1][j] + mark[i][j - 1] - mark[i - 1][j - 1];
				sum += !!(mark[i][j]) * a[i][j];
			}
		answer = max(answer, sum);
	}
	return answer;
}
//======================================================================
ll xRun[MAX], len = 0;

ll getSum(ll x1, ll y1, ll x2, ll y2){
	return a[x2][y2] - a[x2][y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][y1 - 1];
}

ll calculate(ll turn){
	sort(xRun + 1, xRun + len + 1);
	ll sum = 0;
	FOR(ll, i, 1, len - 1){
		ll left = xRun[i], right = xRun[i + 1] - 1;
		if (left > right) continue;
		
		pii range[p + 1] = {}; ll rLen = 0;
		FOR(ll, sq, 1, p){
			Point curr = point[turn][sq];
			ll currLeft = curr.x;
			ll currRight = currLeft + r - 1;

			if (currRight < left || right < currLeft) continue;
			range[++rLen] = {curr.y, curr.y + r - 1};
		}
		
		sort(range + 1, range + 1 + rLen);
		range[++rLen] = {n + 1, n + 1};
		pii curr = range[1];
		FOR(ll, j, 2, rLen){
			pii now = range[j];
			if (now.fi > curr.se){
				sum += getSum(left, curr.fi, right, curr.se);
				curr = now;
			} else
				curr.se = max(curr.se, now.se);
		}
	}
	return sum;
}

ll subFull(){
	FOR(ll, i, 1, n)
		FOR(ll, j, 1, n)
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];

	ll answer = 0;
	FOR(ll, _, 1, k){
		len = 0;
		FOR(ll, i, 1, p){
			ll x = point[_][i].x;
			xRun[++len] = x;
			xRun[++len] = x + r;
		}
		answer = max(answer, calculate(_));
	}
	return answer;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("bonus.inp", "r", stdin);
	freopen("bonus.out", "w", stdout);
	// #endif
	cin >> n >> k >> r >> p;
	FOR(ll, i, 1, n)
		FOR(ll, j, 1, n)
			cin >> a[i][j];
	FOR(ll, _, 1, k)
		FOR(ll, i, 1, p){
			ll x, y; cin >> x >> y;
			point[_][i] = {x, y};
		}

	if (n <= 50 && k <= 50) cout << sub1();
	else cout << subFull();
}