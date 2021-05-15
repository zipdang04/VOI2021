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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

struct Point{ll x, y;};
typedef pair<Point, Point> Rect;
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}

Rect save[5];
Point rect[5];
bool visited[5] = {};
vector<Point> p;
ll answer = INT64_MAX;
map<ll, bool> done;

void check(){
	FOR(int, i, 1, 4)
		FOR(int, j, i + 1, 4){
			Rect one = save[i], two = save[j];
			bool okay = false;
			
			if (max(one.fi.x, two.fi.x) >= min(one.se.x, two.se.x)) okay = true;
			if (max(one.fi.y, two.fi.y) >= min(one.se.y, two.se.y)) okay = true;
			if (okay == false) return;
		}
	ll maxX = INT64_MIN, minX = INT64_MAX;
	ll maxY = INT64_MIN, minY = INT64_MAX;
	FOR(int, i, 1, 4){
		Rect curr = save[i];
		// printf("(%lld/%lld %lld/%lld)", curr.fi.x, curr.fi.y, curr.se.x, curr.se.y);
		minX = min(minX, curr.fi.x);
		minY = min(minY, curr.fi.y);
		maxX = max(maxX, curr.se.x);
		maxY = max(maxY, curr.se.y);
	}
	// printf("(%lld/%lld %lld/%lld)", minX, minY, maxX, maxY);
	// printf("%lld\n", (maxX - minX) * (maxY - minY));
	answer = min(answer, (maxX - minX) * (maxY - minY));
}

Rect process(Point root, Point size, int orient, bool flip){
	if (flip) size = {size.y, size.x};
	if (orient & 1) root.x -= size.x;
	if (orient < 2) root.y -= size.y;
	return {root, root + size};
}

int cnt = 0;
void dqql(ll pos){
	if (pos == 5){check(); return;} 

	FOR(ll, i, 1, 4){
		if (visited[i]) continue;
		visited[i] = true;

		ll len = p.size();
		FOR(ll, ii, 0, len - 1){
			Point curr = p[ii];
			ll x = curr.x, y = curr.y;
			FOR(ll, t1, 0, 3)
				FOR(ll, t2, 0, 1){
					save[i] = process({x, y}, rect[i], t1, t2);
					p.push_back(save[i].fi);
					p.push_back({save[i].fi.x, save[i].se.y});
					p.push_back(save[i].se);
					p.push_back({save[i].se.x, save[i].fi.y});
					dqql(pos + 1);
					p.pop_back();p.pop_back();p.pop_back();p.pop_back();
				}
		}
		visited[i] = false;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	FOR(ll, i, 1, 4) cin >> rect[i].x >> rect[i].y;
	p.push_back({0, 0});
	dqql(1);
	cout << answer;
}