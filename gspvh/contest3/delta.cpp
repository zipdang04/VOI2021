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
typedef map<int, int> mii;	z
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

#define MAX 600005
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

int theta, n, delta, a[MAX];

struct Sub1{
	static int all(){
		int ans = 0;
		FOR(int, _, 1, (1 << n) - 1){
			int msk = _ << 1;
			int mi = INT32_MAX, ma = 0;
			FOR(int, i, 1, n){
				if (!testBit(msk, i)) continue;
				mi = min(mi, a[i]); ma = max(ma, a[i]);
			}
			ans += ma - mi <= delta;
		}
		return ans;
	}

	static int consec(){
		int ans = 0;
		FOR(int, i, 1, n){
			int mi = INT32_MAX, ma = 0;
			FOR(int, j, i, n){
				mi = min(mi, a[j]); ma = max(ma, a[j]);
				if (ma - mi > delta) break;
				ans++;
			}
		}
		return ans;
	}

	static void solve(){
		cout << consec() << ' ' << all();
	}
};

int p2[MAX];
void init(){
	p2[0] = 1;
	FOR(int, i, 1, n)
		p2[i] = (p2[i - 1] << 1) % MOD;
}

struct Sub2{
	void solve(){
		init();
		int consec = 0, all = 0;
		FOR(int, i, 1, n){
			int maxi = a[i] + delta;
			int pos = upper_bound(a + 1, a + 1 + n, maxi) - a - 1;
			int len = pos - i + 1;
			consec += len, all += p2[len - 1];
			consec %= MOD, all %= MOD;
		}
		cout << consec << ' ' << all;
	}
};

const int BIT = 18;
struct Sub3{
	struct Data{int mi, ma;};
	Data process(Data a, Data b){return {min(a.mi, b.mi), max(a.ma, b.ma)};}

	Data rmq[BIT + 1][MAX];
	void initRMQ(){
		FOR(int, i, 0, BIT)
			FOR(int, j, 1, MAX - 1)
				rmq[i][j] = {INT32_MAX, 0};
		FOR(int, i, 1, n)
			rmq[0][i] = {a[i], a[i]};
		FOR(int, bit, 1, BIT)
			FOR(int, i, 1, n)
				rmq[bit][i] = process(rmq[bit - 1][i], rmq[bit - 1][i + (1 << (bit - 1))]);
	}

	int miR[MAX], maR[MAX];
	int consec(){
		initRMQ();
		int ans = 0;
		miR[n + 1] = INT32_MAX, maR[n + 1] = 0;
		FORR(int, i, n, 1)
			miR[i] = min(miR[i + 1], a[i]),
			maR[i] = max(maR[i + 1], a[i]);
		FOR(int, i, 1, n){
			if (maR[i] - miR[i] <= delta){
				ans += n - i + 1;
				ans %= MOD;
				continue;
			}
			int len = 0, pos = i;
			Data init = {INT32_MAX, 0};
			FORR(int, bit, BIT, 0){
				Data curr = process(init, rmq[bit][pos]);
				if (curr.ma - curr.mi > delta) continue;
				len |= 1 << bit; pos += 1 << bit; init = curr;
			}
			ans += len; ans %= MOD;
		}
		return ans;
	}

	int all(){
		init();
		sort(a + 1, a + 1 + n);
		int ans = 0;
		FOR(int, i, 1, n){
			int maxi = a[i] + delta;
			int pos = upper_bound(a + 1, a + 1 + n, maxi) - a - 1;
			int len = pos - i + 1;
			ans += p2[len - 1]; ans %= MOD;
		}
		return ans;
	}

	void solve(){
		int x1 = consec();
		int x2 = all();
		cout << x1 << ' ' << x2 << '\n';
	}

	
};

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("delta.inp", "r", stdin);
	freopen("delta.out", "w", stdout);
	// #endif
	cin >> theta >> n >> delta;
	FOR(int, i, 1, n) cin >> a[i];

	if (theta == 1){
		Sub1::solve();
	} else if (theta == 2){
		Sub2 sub2;
		sub2.solve();
	}
	else if (theta == 3){
		Sub3 sub3;
		sub3.solve();
	}
}