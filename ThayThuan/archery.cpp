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

struct Point {ll x, y;};
typedef pair<Point, ll> Data;
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
ll sqDist(Point p){return p.x * p.x + p.y * p.y;}
ll sqDist(Point a, Point b){return sqDist(a - b);}
bool operator < (Point a, Point b){
	if (a.x < b.x) return true;
	if (a.x > b.x) return false;
	return a.y < b.y;
}

ll n;
set<Data> mission;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(ll, i, 1, n){
		ll t, x, y; cin >> t >> x >> y;
		Point shoot = {x, y};
		Data curr = {shoot, i};

		if (t == 1)
			mission.insert(curr);
		else {
			auto it = upper_bound(mission.begin(), mission.end(), curr);
			ll ans = -1;
			if (it != mission.end()){
				Data now = *it;
				Point center = now.fi;

				if (center.y * center.y > sqDist(shoot, center)) ans = now.se;

				auto it2 = it;
				it2++;
				if (it2 != mission.end()){
					Data now = *it2;
					Point center = now.fi;

					if (center.y * center.y > sqDist(shoot, center)) ans = now.se;
				}
			}
			if (it != mission.begin()){
				auto it2 = it;
				it2--;
				Data now = *it2;
				Point center = now.fi;

				if (center.y * center.y > sqDist(shoot, center)) ans = now.se;
			}
			cout << ans << '\n';
		}
	}
}