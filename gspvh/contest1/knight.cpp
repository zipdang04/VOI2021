#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma") 

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

#define MAX 6001
#define X 2000
#define MOD 998244353

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
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
const Point direc[4] = {{2, -1}, {2, 1}, {1, 2}, {-1, 2}};
bool check(Point p){
	return (p.x >= 0) && (p.y >= 0) && (p.x < MAX) && (p.y < MAX);
}

int f[MAX][MAX];

queue<Point> q;
int cal(Point p){
	if (!check(p)) return 0;
	// if (p.x + p.y < X * 2) return 0;

	int &ans = f[p.x][p.y];
	if (ans >= 0) return ans;
	ans = 0;

	for (Point d: direc){
		Point now = p - d;
		ans += cal(now);
		ans %= MOD;
	}
	return ans;
}
void init(){
	memset(f, -1, sizeof(f));
	f[X][X] = 1;
	FOR(int, i, 0, 6000)
		FOR(int, j, 0, 6000)
			cal({i, j});

	// f[X][X] = 1; q.push({X, X});
	// while (!q.empty()){
	// 	Point curr = q.front(); q.pop();
	// 	int currVal = f[curr.x][curr.y];
		
	// 	for (Point d: direc){
	// 		Point now = curr + d;
	// 		if (!check(now)) continue;
	// 		int &nowVal = f[now.x][now.y];
	// 		if (!nowVal) q.push(now);
	// 		nowVal += currVal, nowVal %= MOD;
	// 	}
	// }
	
}
void fastscan(int &x)
{
	bool neg=false;
	register int c;
	x =0;
	c=getchar();
	if(c=='-')
	{
		neg = true;
		c=getchar();
	}
	for(;(c>47 && c<58);c=getchar())
		x = (x<<1) + (x<<3) +c -48;
	if(neg)
		x *=-1;
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("knight.inp", "r", stdin);
	freopen("knight.out", "w", stdout);
	// #endif
	init();
	int t; fastscan(t);
	FOR(int, i, 1, t){
		int x1, y1, x2, y2; fastscan(x1); fastscan(y1);fastscan(x2);fastscan(y2);
		x2 -= x1 - X, y2 -= y1 - X;
		cout << f[x2][y2] << '\n';
	}
}