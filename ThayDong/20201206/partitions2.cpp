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

#define MAX 101
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

typedef bitset<101> bs;

class Math{
	private:
		ll fact[MAX + 1] = {};
		ll ifac[MAX + 1] = {};
	public:
		Math(){
			fact[0] = 1;
			FOR(ll, i, 1, MAX)
				fact[i] = (fact[i - 1] * i) % MOD;
			ifac[MAX] = pow(fact[MAX], MOD - 2);
			FORR(ll, i, MAX - 1, 0)
				ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;
		}

		ll pow(ll a, ll n){
			if (n == 0) return 1;
			ll ans = pow(a, n >> 1);
			ans *= ans, ans %= MOD;
			if (n & 1) return (ans * a) % MOD;
			return ans;
		}

		ll C(ll n, ll k){
			return (((fact[n] * ifac[k]) % MOD) * ifac[n - k]) % MOD;
		}
		
		ll P(ll n, ll k){
			return (fact[n] * ifac[n - k]) % MOD;
		}
		
		ll factorial(ll n){
			return fact[n];
		}
} math;

class DSU{
	private:
		int n, part; int dsu[MAX];
	public:
		DSU(){n = 0;}
		DSU(int n): n(n){
			part = n;
			FOR(int, i, 1, n) dsu[i] = -1;
		}
		int findRoot(int node){
			if (dsu[node] < 0) return node;
			return dsu[node] = findRoot(dsu[node]);
		}
		bool join(int u, int v){
			u = findRoot(u), v = findRoot(v);
			if (u == v) return false;

			if (dsu[u] > dsu[v]) swap(u, v);
			dsu[u] += dsu[v], dsu[v] = u;
			part--; return true;
		}
		int count(){
			return part;
		}
} *dsu;

ll tmp[MAX][MAX];
ll bell[MAX];
void init(){
	tmp[0][0] = 1;
	FOR(int, i, 1, MAX - 1)
		FOR(int, j, 1, i)
			tmp[i][j] = (tmp[i - 1][j - 1] + j * (tmp[i - 1][j])) % MOD;
	FOR(int, i, 1, MAX - 1)
		FOR(int, j, 1, i)
			bell[i] += tmp[i][j], bell[i] %= MOD;
}

ll n, m;
vl avoid[MAX];
ll f[1 << 10];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	// freopen("partitions2.inp", "r", stdin);
	// freopen("partitions2.out", "w", stdout);
	// #endif
	init(); 
	cin >> n >> m;
	FOR(int, i, 0, m - 1){
		int cnt; cin >> cnt;
		FOR(int, _, 1, cnt){
			int x; cin >> x;
			avoid[i].push_back(x);
		}
	}

	FOR(int, _, 0, (1 << m) - 1){
		dsu = new DSU(n);
		FOR(int, i, 0, m - 1)
			if (testBit(_, i)){
				ll u = avoid[i][0];
				for (ll node: avoid[i]){
					dsu -> join(u, node);
				}
			}
		f[_] = bell[dsu -> count()];
	}
	ll ans = 0;
	FOR(int, _, 0, (1 << m) - 1){
		if (cntBit(_) & 1) ans = (ans + MOD - f[_]) % MOD;
		else ans = (ans + f[_]) % MOD;
	}
	cout << ans << '\n';
}