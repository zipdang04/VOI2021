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

#define MAX 300005

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

ll MOD;
class Math{
	private:
		ll fact[MAX + 1] = {};
		ll ifac[MAX + 1] = {};
	public:
		ll pow(ll a, ll n){
			if (n == 0) return 1;
			ll ans = pow(a, n >> 1);
			ans *= ans, ans %= MOD;
			if (n & 1) return (ans * a) % MOD;
			return ans;
		}
		Math(){
			fact[0] = 1;
			FOR(ll, i, 1, MAX)
				fact[i] = (fact[i - 1] * i) % MOD;
			FORR(ll, i, MAX, 0)
				ifac[i] = pow(fact[i], MOD - 2);
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
};

ll m, n, k;
pii cnv[MAX]; // chuong ngai vat cua chung ta hom nay co 3.14 chu cai
ll way[MAX];

ll finalAns;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k >> MOD;
	Math math = Math();
	finalAns = math.C(m + n - 2, n - 1);
	FOR(ll, i, 1, k){
		cin >> cnv[i].fi >> cnv[i].se;
		cnv[i].fi--, cnv[i].se--;
	}
	
	sort(cnv + 1, cnv + 1 + k);
	FOR(ll, i, 1, k){
		pii pos = cnv[i];
		
		way[i] = math.C(pos.fi + pos.se, pos.fi);
		FOR(ll, j, 1, i - 1){
			pii other = cnv[j];
			other.fi = pos.fi - other.fi, other.se = pos.se - other.se;
			if (other.fi < 0 || other.se < 0) continue;

			way[i] -= way[j] * math.C(other.fi + other.se, other.fi) % MOD;
			way[i] += MOD, way[i] %= MOD;
		}
		
		pos.fi = n - pos.fi - 1, pos.se = m - pos.se - 1;
		finalAns -= way[i] * math.C(pos.fi + pos.se, pos.fi) % MOD;
		finalAns += MOD, finalAns %= MOD;
	}
	cout << finalAns;
}