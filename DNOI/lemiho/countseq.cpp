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

#define MAX 40001
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

int s;
bool notP[MAX];
int prime[MAX], cntP = 0;
void init(){
	FOR(int, i, 2, MAX - 1){
		if (notP[i]) continue;
		prime[++cntP] = i;

		for (ll j = ll(i) * i; j < MAX; j += i)
			notP[j] = true;
	}
}
ll pow2(int n){
	if (n == 0) return 1;
	ll ans = pow2(n >> 1);
	ans *= ans, ans %= MOD;
	
	if (n & 1) ans <<= 1, ans %= MOD;
	return ans;
}

int choice[MAX], ch = 0;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	init();
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> s; ch = 0;
		int save = s;
		
		FOR(int, i, 1, cntP){
			int p = prime[i];
			if (s % p) continue;

			while (s % p == 0) s /= p;
			choice[ch++] = p;
		}
		if (s > 1) choice[ch++] = s;

		s = save;
		int ans = 0;
		FOR(int, mask, 0, (1 << ch) - 1){
			int div = 1;
			FOR(int, i, 0, ch - 1)
				if (testBit(mask, i))
					div *= choice[i];
			int curr = pow2(s / div - 1);
			if (cntBit(mask) & 1) ans = (ans + MOD - curr) % MOD;
			else ans = (ans + curr) % MOD;
		}
		cout << ans << '\n';
	}
}