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

#define MAX 320
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
typedef complex<int> Point;
typedef complex<int> Segment;

int n;
pii CF[MAX];
Point point[MAX];

Point root, convex[MAX]; 
int cLen = 0;

//declare some function
int crossProd(Segment a, Segment b){
	return a.real() * b.imag() - a.imag() * b.real();
}

int area(Point a, Point b, Point c){
	return crossProd(b - a, c - a);
}

bool isCCW(Point a, Point b, Point c){
	return area(a, b, c) > 0;
}

bool cmpAngle(Point a, Point b){
	return isCCW(root, a, b);
}
//=========================



void buildConvex(){
	Point prev = root, curr = point[2];
	convex[++cLen] = prev;
	convex[++cLen] = curr;
	
	FOR(int, i, 3, n){
		Point next = point[i];
		while (cLen > 2 && !isCCW(prev, curr, next)){
			curr = prev; cLen--;
			prev = convex[cLen - 1];
		}
		convex[++cLen] = next;
		prev = curr, curr = next;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n;
	FOR(int, i, 1, n){
		int x, y; cin >> x >> y;
		CF[i] = {x, y};
	}
	//=========================
	//init
	sort(CF + 1, CF + 1 + n);

	FOR(int, i, 1, n) point[i] = Point(CF[i].fi, CF[i].se);
	root = point[1];
	
	sort(point + 2, point + 1 + n, cmpAngle);
	buildConvex();
	//=========================
	int ans = 0;
	if (cLen == 3){
		Point a = convex[1], b = convex[2], c = convex[3];
		FOR(int, i, 1, n){
			Point curr = point[i];
			if (curr == a || curr == b || curr == c) continue;
			
			int sA = area(a, b, curr);
			int sB = area(b, c, curr);
			int sC = area(c, a, curr);
			ans = max(ans, sA + sB);
			ans = max(ans, sB + sC);
			ans = max(ans, sC + sA);
		}
	} else {
		FOR(int, i, 1, cLen){
			FOR(int, j, i + 2, cLen){
				if (i == 1 && j == cLen) continue;
				
				int up = 0;
				FOR(int, mid, i + 1, j - 1)
					up = max(up, area(convex[i], convex[mid], convex[j]));
				
				int down = 0;
				for (int mid = j % cLen + 1; mid != i; mid = mid % cLen + 1){
					if (mid > cLen) {cout << "s"; return 0;}
					if (mid < 1) {cout << "s"; return 0;}
					down = max(down, area(convex[j], convex[mid], convex[i]));
				}
				
				ans = max(ans, up + down);
			}
		}
		// FOR(int, i, 1, cLen)
	}
	if (ans & 1) cout << ans / 2 << ".5";
	else cout << ans / 2;
}