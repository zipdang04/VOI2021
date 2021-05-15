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

#define MAX 100001
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

int n, k;
int base[MAX];
vi tree[MAX];

struct Sub1{
	int f[501][501] = {};
	const int NaN = 10000;
	vi alrite;
	void init(){
		FOR(int, i, 1, n){
			FOR(int, j,1 , n) f[i][j] = NaN;

			f[i][i] = 0;
			for (int child: tree[i])
				f[i][child] = 1;
		}
	}

	void floyd(){
		FOR(int, k, 1, n)
			FOR(int, i, 1, n)
				FOR(int, j, 1, n)
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	}

	void solve(){
		FOR(int, i, 1, n){
			vi save;
			FOR(int, j, 1, k)
				save.push_back(f[i][base[j]]);

			sort(save.begin(), save.end());
			bool okay = true;
			FOR(int, j, 1, k - 1)
				if (save[j] == save[j - 1]) {
					okay = false; break;
				}
			
			if (okay) alrite.push_back(i);
		}
	}

	Sub1(){
		init();
		floyd();
		solve();
		cout << alrite.size() << '\n';
		for (int i: alrite) cout << i << ' '; cout << '\n';
	}
};

struct Sub2{
	int f[MAX][301];
	int cnt[MAX];
	vi alrite;

	void bfs(int root, int pos){
		queue<int> q;
		f[root][pos] = 1; q.push(root);
		while (!q.empty()){
			int node = q.front(); q.pop();
			int len = f[node][pos] + 1;

			for (int child: tree[node]){
				if (f[child][pos]) continue;
				f[child][pos] = len; q.push(child);
			}
		}
	}

	bool check(int node){
		bool okay = true;
		FOR(int, i, 1, k){
			int num = f[node][i];
			if (cnt[num]) okay = false;
			cnt[num]++;
		}
		FOR(int, i, 1, k) cnt[f[node][i]]--;
		return okay;
	}

	Sub2(){
		FOR(int, i, 1, k) bfs(base[i], i);
		FOR(int, i, 1, n)
			if (check(i)) alrite.push_back(i);
		
		cout << alrite.size() << '\n';
		for (int i: alrite) cout << i << ' ';
	}
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef HIEU
	freopen("military.inp", "r", stdin);
	freopen("military.out", "w", stdout);
	// #endif
	cin >> n >> k;
	FOR(int, i, 1, k) cin >> base[i];
	FOR(int, i, 1, n - 1){
		int u, v; cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	if (n <= 500)
		Sub1 sub1;
	else
		Sub2 sub2;
}