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

struct Point{int x, y;};
typedef pair<Point, Point> Segment;

int n;
int x[MAX], y[MAX];
int maX, maY;
int matchX[MAX], matchY[MAX];
Point p[MAX];
Segment seg[4][MAX]; int len[4] = {};

bool cmpX(Segment a, Segment b){return a.fi.x < b.fi.x;}
bool cmpY(Segment a, Segment b){return a.fi.y < b.fi.y;}

int nen(int *arr, int *match){
	map<int, int> s;
	FOR(int, i, 1, n)
		s[arr[i]] = true;
	
	int tmp = 0;
	for (pii i: s){
		s[i.fi] = ++tmp;
		match[tmp] = i.fi;
	}

	FOR(int, i, 1, n)
		arr[i] = s[arr[i]];
	return tmp;
}

ll processX(Segment *arr, int len){
	bool forward = false;
	if (arr[1].fi.x == 1) forward = true;

	bool good[maY + 1] = {};
	ll answer = 0;
	if (forward){
		FOR(int, i, 1, len){
			Segment curr = arr[i];
			int start = curr.fi.y, end = curr.se.y;
			if (start > end) swap(start, end);

			FOR(int, i, start + 1, end){
				if (good[i]) answer += matchY[i] - matchY[i - 1];
				good[i] = true;
			}
		}
	} else {
		FORR(int, i, len, 1){
			Segment curr = arr[i];
			int start = curr.fi.y, end = curr.se.y;
			if (start > end) swap(start, end);

			FOR(int, i, start + 1, end){
				if (good[i]) answer += matchY[i] - matchY[i - 1];
				good[i] = true;
			}
		}
	}
	return answer;
}

ll processY(Segment *arr, int len){
	bool forward = false;
	if (arr[1].fi.y == 1) forward = true;

	bool good[maX + 1] = {};
	ll answer = 0;
	if (forward){
		FOR(int, i, 1, len){
			Segment curr = arr[i];
			int start = curr.fi.x, end = curr.se.x;
			if (start > end) swap(start, end);

			FOR(int, i, start + 1, end){
				if (good[i]) answer += matchX[i] - matchX[i - 1];
				good[i] = true;
			}
		}
	} else {
		FORR(int, i, len, 1){
			Segment curr = arr[i];
			int start = curr.fi.x, end = curr.se.x;
			if (start > end) swap(start, end);

			FOR(int, i, start + 1, end){
				if (good[i]) answer += matchX[i] - matchX[i - 1];
				good[i] = true;
			}
		}
	}
	return answer;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n) cin >> x[i] >> y[i];
	maX = nen(x, matchX); maY = nen(y, matchY);

	FOR(int, i, 1, n) p[i] = {x[i], y[i]};

	FOR(int, i, 1, n){
		Point one = p[i], two = p[i % n + 1];
		if (one.x == two.x){
			if (one.y > two.y) 
				seg[0][++len[0]] = {one, two};
			else 
				seg[1][++len[1]] = {one, two};
		} else {
			if (one.x > two.x) 
				seg[2][++len[2]] = {one, two};
			else 
				seg[3][++len[3]] = {one, two};
		}
	}
	sort(seg[0] + 1, seg[0] + len[0] + 1, cmpX);
	sort(seg[1] + 1, seg[1] + len[1] + 1, cmpX);
	sort(seg[2] + 1, seg[2] + len[2] + 1, cmpY);
	sort(seg[3] + 1, seg[3] + len[3] + 1, cmpY);
	cout << processX(seg[0], len[0])
		  + processX(seg[1], len[1])
		  + processY(seg[2], len[2])
		  + processY(seg[3], len[3]);
}