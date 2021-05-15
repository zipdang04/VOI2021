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

struct Point{int x, y, z;};
struct Box{int xMi, xMa, yMi, yMa, zMi, zMa;};
const Box NaN = {-1, -1, -1, -1, -1, -1};

bool operator == (Box a, Box b){
	return a.xMa == b.xMa
		&& a.xMi == b.xMi
		&& a.yMa == b.yMa
		&& a.yMi == b.yMi
		&& a.zMa == b.zMa
		&& a.zMi == b.zMi;
}

Box makeBox(Point p, int radius){
	return {p.x - radius, p.x + radius,
			p.y - radius, p.y + radius,
			p.z - radius, p.z + radius};
}

Box cut(Box a, Box b){
	Box ans;
	if (a.xMa < b.xMi || b.xMa < a.xMi) return NaN;
	ans.xMi = max(a.xMi, b.xMi);
	ans.xMa = min(a.xMa, b.xMa);
	if (a.yMa < b.yMi || b.yMa < a.yMi) return NaN;
	ans.yMi = max(a.yMi, b.yMi);
	ans.yMa = min(a.yMa, b.yMa);
	if (a.zMa < b.zMi || b.zMa < a.zMi) return NaN;
	ans.zMi = max(a.zMi, b.zMi);
	ans.zMa = min(a.zMa, b.zMa);
	return ans;
}

int n;
Point p[MAX];

bool check(int radius){
	Box box = makeBox(p[1], radius);	
	FOR(int, i, 2, n){
		Box curr = makeBox(p[i], radius);
		box = cut(box, curr);
		if (box == NaN) return false;
	}
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(int, i, 1, n){
		int x, y, z; cin >> x >> y >> z;
		p[i] = {x, y, z};
	}

	int left = 0, right = 1000000000, ans = 1000000000;
	while (left <= right){
		int mid = (left + right) >> 1;
		if (check(mid)) ans = mid, right = mid - 1;
		else left = mid + 1;
	}
	cout << ans;
}