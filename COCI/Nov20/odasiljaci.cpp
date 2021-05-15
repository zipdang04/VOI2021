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

struct Point{ll x, y;};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
ll sqDist(Point seg){return seg.x * seg.x + seg.y * seg.y;}
ll sqDist(Point a, Point b){return sqDist(a - b);}
bool operator < (Point a, Point b){return sqDist(a) < sqDist(b);}

ll n;
Point point[MAX];
pair<ll, pll> edge[MAX]; ll total = 0;

ll dsu[MAX];
ll findRoot(ll node){
	if (dsu[node] < 0) return node;
	return dsu[node] = findRoot(dsu[node]);
}
bool join(ll u, ll v){
	u = findRoot(u), v = findRoot(v);
	if (u == v) return false;

	if (dsu[u] > dsu[v]) swap(u, v);
	dsu[u] += dsu[v], dsu[v] = u;
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(ll, i, 1, n) dsu[i] = -1;
	FOR(ll, i, 1, n){
		ll x, y; cin >> x >> y;
		point[i] = {x, y};
	}

	FOR(ll, i, 1, n)
		FOR(ll, j, i + 1, n)
			edge[++total] = {sqDist(point[i], point[j]), {i, j}};
	sort(edge + 1, edge + 1 + total);
	ll answer = 0;
	FOR(ll, i, 1, total){
		pair<ll, pll> curr = edge[i];
		ll dist = curr.fi, u = curr.se.fi, v = curr.se.se;
		if (join(u, v))
			answer = max(answer, dist);
	}
	cout << fixed << setprecision(7) << (sqrt(answer) / 2.0);
}