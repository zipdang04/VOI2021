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

#define MAX 10001
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

const ld PI = acos(-1);

//==================================================================
struct Point{ll x, y;};

Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}

ll cross(Point a, Point b){return a.x * b.y - a.y * b.x;}
ll dot(Point a, Point b){return a.x * b.x + a.y * b.y;}

bool ccw(Point a, Point b){return cross(a, b) > 0;}
bool ccw(Point a, Point b, Point c){return cross(b - a, c - a) > 0;}

ld abs(Point a){return sqrt(a.x * a.x + a.y * a.y);}
ld abs(Point a, Point b){return abs(b - a);}
//==================================================================
ll n, r;
Point mine[MAX];
Point convex[MAX]; ll len = 0;

bool cmp(Point a, Point b){
	return ccw(mine[0], a, b);
}

void buildCVH(){
	FOR(ll, i, 1, n - 1){
		Point curr = mine[i];
		while (len >= 2){
			if (ccw(convex[len - 2], convex[len - 1], curr)) break;
			len--;
		}
		convex[len++] = curr;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n >> r;
	FOR(ll, i, 0, n - 1){
		ll x, y; cin >> x >> y;
		mine[i] = {x, y};
	}
	//=========================
	//init
	FOR(ll, i, 1, n - 1)
		if (mine[i].x < mine[i - 1].x) 
			swap(mine[i], mine[i - 1]);
		else if (mine[i].x == mine[i - 1].x && mine[i].y < mine[i - 1].y)
			swap(mine[i], mine[i - 1]);
	sort(mine + 1, mine + n, cmp);
	//=========================
	//convex hull
	convex[len++] = mine[0];
	buildCVH();
	//=========================
	//getAns
	ld total = 0;
	FOR(ll, i, 0, len - 1){
		total += abs(convex[i], convex[(i + 1) % len]);
	}
	ld totalAngle = 0;
	FOR(ll, i, 0, len - 1){
		Point curr = convex[i],
			  prev = convex[(i + len - 1) % len],
			  next = convex[(i + 1) % len];
		prev = prev - curr, next = next - curr;
		totalAngle += PI - abs(acos(dot(prev, next) / (abs(prev) * abs(next))));
	}
	total += totalAngle * r * r;
	//=========================
	cout << fixed << setprecision(3) << total;
}
