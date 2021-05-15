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
#define MOD 998244353

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

ll minX, posX, minY, posY;
ll n;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	FOR(ll, i, 1, n){
		ll num; cin >> num;
		if (num < 0) minX++;
		else posX++;
	}
	FOR(ll, i, 1, n){
		ll num; cin >> num;
		if (num < 0) minY++;
		else posY++;
	}

	ll ans = 0;
	FOR(ll, i, 0, max(minX, minY)){
		ll remainX = minX - i;
		ll remainY = minY - i;

		if (remainX > posY) continue;
		if (remainX < 0) continue;
		if (remainY < 0) continue;

		ll curr = ((math.C(minX, i) * math.C(minY, i)) % MOD) 
				* ((math.C(posY, remainX) * math.C(posX, remainY)) % MOD) % MOD;
		ans += curr;
		ans %= MOD;
	}
	cout << ans << '\n';
}