#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma") 
  
#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 50005
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
ll sqDist(Point p){return p.x * p.x + p.y * p.y;}
ll sqDist(Point a, Point b){return sqDist(a - b);}
bool cmpX(pair<Point, ll> a, pair<Point, ll> b){return (a.fi.x != b.fi.x) ? (a.fi.x < b.fi.x) : (a.fi.y < b.fi.y);}
bool cmpY(pair<Point, ll> a, pair<Point, ll> b){return (a.fi.y != b.fi.y) ? (a.fi.y < b.fi.y) : (a.fi.x < b.fi.x);}

ll n;
pair<Point, ll> p[MAX];

pair<ll, pii> closest(ll left, ll right){
	ll len = right - left + 1;
	if (len == 2) return {sqDist(p[left].fi, p[right].fi), {p[left].se, p[right].se}};
	if (len == 3){
		Point a = p[left].fi, b = p[left + 1].fi, c = p[left + 2].fi;
		ll posA = p[left].se, posB = p[left + 1].se, posC = p[left + 2].se;
		return min(
			min(
				pair<ll, pii>(sqDist(a, b), pii(posA, posB)), 
				pair<ll, pii>(sqDist(b, c), pii(posB, posC))
			), 
			{sqDist(a, c), {posA, posC}}
		);
	}

	ll mid = (left + right) >> 1;
	pair<ll, pii> ans = min(closest(left, mid), closest(mid + 1, right));
	// cerr << left << '-' << right << ": " << ans.fi << ' ' << ans.se.fi << ' ' << ans.se.se << '\n';
	
	pair<Point, ll> r[MAX] = {}; ll cnt = 0;
	r[++cnt] = p[mid];
	FORR(ll, i, mid - 1, left){
		ll tmp = p[mid].fi.x - p[i].fi.x; tmp *= tmp;
		if (tmp > ans.fi) break;
		else r[++cnt] = p[i];
	}
	FOR(ll, i, mid + 1, right){
		ll tmp = p[i].fi.x - p[mid].fi.x; tmp *= tmp;
		if (tmp > ans.fi) break;
		else r[++cnt] = p[i];
	}
	sort(r + 1, r + 1 + cnt, cmpY);
	// FOR(ll, i, 1, cnt) cerr << r[i].fi.x << '/' << r[i].fi.y << ' ' << r[i].se << '\n';
	FOR(ll, i, 1, cnt)
		FOR(ll, j, i + 1, min(i + 7, cnt))
			ans = min(ans, {sqDist(r[i].fi, r[j].fi), {r[i].se, r[j].se}});
	// cerr << left << '-' << right << ": " << ans.fi << ' ' << ans.se.fi << ' ' << ans.se.se << '\n';
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; FOR(ll, i, 1, n){ll x, y; cin >> x >> y; p[i] = {{x, y}, i};}
	sort(p + 1, p + 1 + n, cmpX);	
	// FOR(ll, i, 1, n) cerr << p[i].fi.x << '/' << p[i].fi.y << ' ' << p[i].se << '\n';
	pair<ll, pii> ans = closest(1, n);
	if (ans.se.fi > ans.se.se) swap(ans.se.fi, ans.se.se);
	cout << ans.se.fi - 1 << ' '  << ans.se.se - 1 <<  ' ' << fixed << setprecision(6) << sqrt(ans.fi);
}