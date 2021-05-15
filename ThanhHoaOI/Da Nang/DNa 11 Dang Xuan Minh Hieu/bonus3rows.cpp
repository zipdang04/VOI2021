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

#define MAX 1000006
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

int n, q;

int forw[4][MAX];
int bakw[4][MAX];

struct Sub1{
	int x, y, u, v; 
	ll f[5][MAX];
	int dpForw(){
		FOR(int, i, 1, 3)
			FOR(int, j, 1, n)
				f[i][j] = INT64_MIN;
		f[x][y] = 0;
		FOR(int, i, x, u)
			FOR(int, j, y, v){
				f[i][j] += forw[i][j];
				f[i + 1][j] = max(f[i + 1][j], f[i][j]);
				f[i][j + 1] = max(f[i][j + 1], f[i][j]);
			}
		return f[u][v];
	}
	int dpBakw(){
		FOR(int, i, 1, 3)
			FOR(int, j, 1, n)
				f[i][j] = INT64_MIN;
		f[x][y] = 0;
		FOR(int, i, x, u)
			FOR(int, j, y, v){
				f[i][j] += bakw[i][j];
				f[i + 1][j] = max(f[i + 1][j], f[i][j]);
				f[i][j + 1] = max(f[i][j + 1], f[i][j]);
			}
		return f[u][v];
	}

	Sub1(){
		FOR(int, _, 1, q){
			cin >> x >> y >> u >> v;
			if (y > v) swap(x, u), swap(y, v);
			
			if (x <= u) cout << dpForw() << '\n';
			else{
				x = 4 - x, u = 4 - u;
				cout << dpBakw() << '\n';
			}
		}
		
	}
};

struct Sub2{
	class SegTree{
		private:
			ll len;
			ll it[MAX * 4];

			void update(ll ind, ll left, ll right, ll pos, ll val){
				if (left == right){
					it[ind] = val;
					return;
				}

				ll y = ind << 1, mid = (left + right) >> 1;
				if (pos <= mid) update(y, left, mid, pos, val);
				else update(y + 1, mid + 1, right, pos, val);

				it[ind] = min(it[y], it[y + 1]);
			}

			ll get(ll ind, ll left, ll right, ll posL, ll posR){
				if (right < posL || posR < left) return INT64_MAX;
				if (posL <= left && right <= posR) return it[ind];
				
				ll y = ind << 1, mid = (left + right) >> 1;
				return min(
					get(y, left, mid, posL, posR),
					get(y + 1, mid + 1, right, posL, posR)
				);
			}
		public:
			SegTree(ll len): len(len){
				FOR(ll, i, 1, 4 * len) it[i] = INT64_MAX;
			}
			
			void update(ll pos, ll val) {update(1, 1, len, pos, val);}
			ll get(ll posL, ll posR) {
				if (posR < posL) return INT64_MAX;
				return get(1, 1, len, posL, posR);
			}
	};
	SegTree *segF[4], *segB[4];
	
	ll sumF[4][MAX], sumB[4][MAX];
	ll changeF[4][MAX], changeB[4][MAX];

	void init(){
		FOR(int, r, 1, 3){
			sumF[r][0] = sumB[r][0] = 0;
			FOR(int, c, 1, n)
				sumF[r][c] = sumF[r][c - 1] + forw[r][c],
				sumB[r][c] = sumB[r][c - 1] + bakw[r][c];
		}
		FOR(int, r, 2, 3){
			changeF[r][0] = changeB[r][0] = 0;

			FOR(int, c, 1, n - 1)
				changeF[r][c] = forw[r][c] - forw[r - 1][c + 1] + changeF[r][c - 1],
				changeB[r][c] = bakw[r][c] - bakw[r - 1][c + 1] + changeB[r][c - 1];
			segF[r] = new SegTree(n);
			segB[r] = new SegTree(n);
			FOR(int, c, 1, n - 1)
				segF[r] -> update(c, changeF[r][c]),
				segB[r] -> update(c, changeB[r][c]);
		}
	}

	int x, y, u, v; 
	ll dpForw(){
		if (x == u) return sumF[x][v] - sumF[x][y - 1];
		cerr << x << ' ' << y << ' ' << u << ' ' << v << '\n';
		ll answer = sumF[x][v] - sumF[x][y - 1] + forw[u][v];
		ll add = changeF[u][v - 1] - min(0ll, (segF[u] -> get(1, v - 1)));
		answer += max(0ll, add);
		return answer;
	}
	ll dpBakw(){
		if (x == u) return sumB[x][v] - sumB[x][y - 1];
		cerr << x << ' ' << y << ' ' << u << ' ' << v << '\n';
		ll answer = sumB[x][v] - sumB[x][y - 1] + bakw[u][v];
		ll add = changeB[u][v - 1] - min(0ll, (segB[u] -> get(1, v - 1)));
		answer += max(0ll, add);
		return answer;
		// 
	}

	Sub2(){
		init();
		FOR(int, _, 1, q){
			cin >> x >> y >> u >> v;
			if (y > v) swap(x, u), swap(y, v);
			
			if (x <= u) cout << dpForw() << '\n';
			else{
				x = 4 - x, u = 4 - u;
				cout << dpBakw() << '\n';
			}
		}
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen("bonus3rows.inp", "r", stdin);
	freopen("bonus3rows.out", "w", stdout);

	cin >> n >> q;
	FOR(int, i, 1, 3){
		FOR(int, j, 1, n) cin >> forw[i][j];
		FOR(int, j, 1, n) bakw[4 - i][j] = forw[i][j];
	}
	if (n * q <= 1000000) Sub1 sub1;
	else Sub2 sub2;
}