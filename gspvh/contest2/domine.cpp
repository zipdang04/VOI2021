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

#define MAX 1001
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

const ll oo = 1e18;

ll r, c, k;
ll num[MAX][5];
bool visited[MAX][5];
//===============================================
ll test(ll remain, ll sum){
	if (remain == 0) return sum;
	ll ans = INT64_MIN;

	FOR(ll, i, 1, r)
		FOR(ll, j, 1, c - 1){
			if (visited[i][j] || visited[i][j + 1]) continue;
			visited[i][j] = visited[i][j + 1] = true;
			ll curr = sum + num[i][j] + num[i][j + 1];
			ans = max(ans, test(remain - 1, curr));
			visited[i][j] = visited[i][j + 1] = false;
		}
	FOR(ll, i, 1, r - 1)
		FOR(ll, j, 1, c){
			if (visited[i][j] || visited[i + 1][j]) continue;
			visited[i][j] = visited[i + 1][j] = true;
			ll curr = sum + num[i][j] + num[i + 1][j];
			ans = max(ans, test(remain - 1, curr));
			visited[i][j] = visited[i + 1][j] = false;
		}
	return ans;
}
ll sub1(){
	return test(k, 0);
}
//===============================================
ll f2[MAX][MAX];
ll sub2(){
	FOR(ll, i, 0, r)
		FOR(ll, j, 0, k)
			f2[i][j] = -oo;

	f2[0][0] = 0;
	FOR(ll, i, 2, r){
		ll curr = num[i][1] + num[i - 1][1];
		f2[i][1] = curr;
		FOR(ll, j, 2, k){
			if (f2[i - 2][j - 1] != -oo) 
				f2[i][j] = f2[i - 2][j - 1] + curr;
		}
		FOR(ll, j, 1, k)
			f2[i][j] = max(f2[i][j], f2[i - 1][j]);
	}
	return f2[r][k];
}
//===============================================
ll f[1001][2001][16] = {};
ll allRMask[4] = {3, 6, 12, 15};
ll sub5(){
	FOR(int, i, 1, r)
		FOR(int, j, 1, k)
			FOR(int, msk, 0, 15)
				f[i][j][msk] = -oo;

	f[1][0][0] = 0;
	int allMsk = (1 << c) - 1;
	FOR(int, i, 1, r){
		FOR(int, j, 1, k){
			FOR(int, msk, 0, allMsk){
				if (f[i][j][msk] == -oo) continue;

				int remainMsk = allMsk;	
				
			}
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("domine.inp", "r", stdin);
	freopen("domine.out", "w", stdout);
	// #endif
	cin >> r >> c >> k;
	FOR(ll, i, 1, r)
		FOR(ll, j, 1, c)
			cin >> num[i][j];
	if (r <= 5) cout << sub1();
	else if (c <= 1) cout << sub2();
	else assert(false);
}