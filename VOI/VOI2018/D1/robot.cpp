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

#define MAX 1003
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
const Point direc[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
Point operator + (Point a, Point b) {return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b) {return {a.x - b.x, a.y - b.y};}
bool operator == (Point a, Point b) {return (a.x == b.x && a.y == b.y);}
bool operator != (Point a, Point b) {return !(a == b);}
Point operator * (Point a, ll b) {return {a.x * b, a.y * b};}

ll n, x, y, s;
char maze[MAX][MAX];

bool isBlank(Point p){
	return (p.x < 1) || (p.y < 1) || (p.x > n) || (p.y > n) || (maze[p.y][p.x] == '.');
}
bool inside(Point p){
	return (p.x >= 1) && (p.y >= 1) && (p.x <= n) && (p.y <= n);
}

void sub1(){
	Point curr = {x, y}; ll d = 0;
	ll cnt = s;
	while (cnt){
		--cnt;
		while (!isBlank(curr + direc[d])) d = (d + 1) & 3;
		curr = curr + direc[d];
	}
	cout << curr.x << ' ' << curr.y;
}

pair<Point, int> road[2000001]; const int roadLen = 2000000;
void makeRoad(Point root){
	road[0] = {root, 0};
	int d = 0;
	FOR(int, i, 1, roadLen){
		while (!isBlank(root + direc[d])) d = (d + 1) & 3;
		root = root + direc[d];
		road[i] = {root, d};
	}
}
void sub2(){
	Point curr = {x, y};
	ll cnt = s;
	if (x < 1 || x > n){
		curr = curr + direc[0] * cnt;
		cout << curr.x << ' ' << curr.y;
		return;
	}

	if (y > n){
		ll tmp = curr.y - (n + 1);
		if (tmp >= cnt){
			curr = curr + direc[0] * cnt;
			cout << curr.x << ' ' << curr.y;
			return;
		}
		curr = curr + direc[0] * tmp; cnt -= tmp;
	}
	makeRoad(curr);
	if (cnt <= roadLen){
		curr = road[cnt].fi;
		cout << curr.x << ' ' << curr.y;
		return;
	}

	if (!inside(road[roadLen].fi)){
		Point dir = road[roadLen].fi - road[roadLen - 1].fi;
		int pos = 0;
		FOR(int, i, 1, roadLen)
			if (!inside(road[i].fi)){
				curr = road[i].fi, pos = i; break;
			}
		cnt -= pos;
		curr = curr + dir * cnt;
		cout << curr.x << ' ' << curr.y;
		return;
	} else {
		int start, cycle;
		int hare = 2, tortoise = 1;
		while (road[hare] != road[tortoise])
			hare += 2, tortoise++;
		
		hare = 0;
		while (road[hare] != road[tortoise])
			hare++, tortoise++;
		start = hare;
		
		tortoise = hare + 1;
		while (road[hare] != road[tortoise])
			tortoise++;
		cycle = tortoise - hare;
		
		cnt -= start; curr = road[start].fi;
		cnt %= cycle; curr = road[start + cnt].fi;
		cout << curr.x << ' ' << curr.y;
		return;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("robot.inp", "r", stdin);
	freopen("robot.out", "w", stdout);
	// #endif
	cin >> n >> x >> y >> s;
	FOR(ll, i, 1, n) cin >> maze[i] + 1;

	if (s <= 100000) sub1();
	else sub2();
}