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

#define MAX 200001
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

struct Point {int x, y;};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};};
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};};

#define MISS 1
#define SHOOT 2
struct Query {int type; Point p;};
Query que[MAX];

int n;
set<int> xSave, ySave[MAX];
int xVal[MAX], xLen;
vi yVal[MAX];

const int oo = 1e9 + 7;
vi bitL[MAX], bitR[MAX];

void init(){
	for (int num: xSave) xVal[++xLen] = num;
	// // FOR(int, i, 1, xLen) cerr << xVal[i] << ' '; cerr << '\n';
	FOR(int, i, 1, n) {
		Query curr = que[i];
		// if (curr.type == SHOOT) continue;

		Point p = curr.p;
		int pos = lower_bound(xVal + 1, xVal + xLen, p.x) - xVal;
		ySave[pos].insert(p.y);
	}
	FOR(int, i, 1, xLen){
		yVal[i] = vi(ySave[i].begin(), ySave[i].end());
		yVal[i].insert(yVal[i].begin(), 0);
		yVal[i].push_back(oo);
		FOR(int, j, 1, yVal[i].size() - 1)
			bitL[i] = bitR[xLen - i + 1] = vi(yVal[i].size(), -oo);
	}
}

void update(vi *bit, bool rev, int x2, int y2, int val){
	// cerr << "upd: " << rev << ' ' << x2 << ' ' << y2 << ' ' << val << '\n';
	int posX = upper_bound(xVal + 1, xVal + xLen + 1, x2) - xVal - 1;
	int findX = posX;
	if (rev) posX = xLen - posX + 1, val = -val;

	for (int x = posX; x <= xLen; x += x & -x){
		int posY = upper_bound(yVal[findX].begin() + 1, yVal[findX].end(), y2) - yVal[findX].begin();
		// cerr << x << "." << posY << '\n';
		int szY = bit[x].size();
		for (int y = posY; y < szY; y += y & -y){
			bit[x][y] = max(bit[x][y], val);
			// cerr << x << '/' << y << ' ' << bit[x][y] << '\n';
		}
	}
}

int get(vi *bit, bool rev, int x2, int y2){
	// cerr << "ask: " << rev << ' ' << x2 << ' ' << y2 << '\n';
	int posX = upper_bound(xVal + 1, xVal + xLen + 1, x2) - xVal - 1;
	int findX = posX;
	if (rev) posX = xLen - posX + 1;

	int ans = -oo;
	for (int x = posX; x; x -= x & -x){
		int posY = upper_bound(yVal[findX].begin() + 1, yVal[findX].end(), y2) - yVal[findX].begin();
		// cerr << x << "." << posY << '\n';
		int szY = bit[x].size();
		for (int y = posY; y; y -= y & -y){
			ans = max(ans, bit[x][y]);
			// cerr << x << '/' << y << ' ' << bit[x][y]<< '\n';
		}
	}

	if ((ans != -oo) && rev)
		ans = -ans;
	// cerr << "ans: " << ans << '\n';
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n){
		int t, x, y; cin >> t >> x >> y;
		que[i] = {t, x, -y};
		xSave.insert(x);
	}
	init();

	FOR(int, i, 1, n){
		Query curr = que[i];
		Point p = curr.p;
		if (curr.type == MISS){
			update(bitL, false, p.x, p.y, i);
			update(bitR, true, p.x, p.y, i);
		} else {
			int thresY = -((-p.y) / 2 + 1);
			int nearL = get(bitL, false, p.x, thresY);
			int nearR = get(bitR, true, p.x, thresY);
			// cerr << nearL << ' ' << nearR << '\n';

			int ans = -1;
			if (nearL != -oo){
				Point cir = que[nearL].p;
				Point diff = p - cir;
				if (diff.x * diff.x + diff.y * diff.y < cir.y * cir.y)
					ans = nearL;
			}
			if (nearR != -oo){
				Point cir = que[nearR].p;
				Point diff = p - cir;
				if (diff.x * diff.x + diff.y * diff.y < cir.y * cir.y)
					ans = nearR;
			}
			cout << ans << '\n';
		}
	}
}