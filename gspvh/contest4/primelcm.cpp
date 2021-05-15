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

#define MAX 10000001
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

ll mul(ll a, ll b, ll lim){
	return (a == -1 || b == -1) ? -1 : (
		(a > b / lim) ? -1 : (a * b)
	);
}

ll power(ll a, ll n, ll lim){
	if (n == 0) return 1;
	ll ans = power(a, n >> 1);
	ans = mul(ans, ans, lim);
	if (n & 1)
}

ll power(ll a, ll n){
	if (n == 0) return 1;
	ll ans = power(a, n >> 1);
	ans *= ans, ans %= MOD;
	if (n & 1) return (ans * a) % MOD;
	return ans;
}

bool notP[MAX];
int prime[MAX], prLen = 0;
void init(){
	FOR(ll, i, 2, MAX - 1){
		if (notP[i]) continue;
		prime[++prLen] = i;
		for (ll j = i * i; j < MAX; j += i)
			notP[j] = true;
	}
}
ll t, n[MAX];

struct Sub1{
	ll n;

	ll __lcm(ll a, ll b){
		return a / __gcd(a, b) * b;
	}

	bool isP(ll num){
		if (num <= 1) return false;
		FOR(ll, i, 2, num){
			if (i * i > num) break;
			if (num % i) continue;
			return false;
		}
		return true;
	}

	Sub1(ll n): n(n){
		ll lcm = 1;
		FOR(ll, i, 2, n){
			lcm = __lcm(lcm, i);
		}
		FOR(ll, i, 2, n)
			if (isP(i)) lcm /= i;
		cout << lcm << ' ';
	}
};

struct Sub2{
	ll n;
	Sub2(ll n): n(n){
		ll ans = 1;
		FOR(int, i, 1, prLen){
			ll pr = prime[i];
			if (pr * pr > n) break;
			ll x = 1, tmp = pr;
			while (true){
				if (tmp > n / pr) break;
				tmp *= pr;
				x++; 
				ans *= pr; ans %= MOD;
			}
		}
		cout << ans << ' ';
	}
};

struct Sub3{
	// 
};

ll checkSub(){
	bool l20 = true, l1e6 = true;
	FOR(int, i, 1, t){
		if (n[i] > 20) l20 = false;
		if (n[i] > 1000000) l1e6 = false;
	}
	if (l20) return 1;
	else if (t <= 10 && l1e6) return 2;
	else if (l1e6) return 3;
	else if (t <= 10) return 4;
	else return 5;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	// #ifndef ONLINE_JUDGE
	freopen("primelcm.inp", "r", stdin);
	freopen("primelcm.out", "w", stdout);
	// #endif
	init();
	cin >> t;
	FOR(int, _, 1, t) cin >> n[_];

	ll subtask = checkSub();
	if (subtask == 1){
		FOR(int, i, 1, t){
			Sub1 sub1(n[i]);
		}
	} else if (subtask <= 4){
		FOR(int, i, 1, t)
			Sub2 sub2(n[i]);
	} else {
		// 
	}
}