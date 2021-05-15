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

ll n, k;
ll answer;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	// answer = math.pow(k, n * n);
	// cerr << "begin:" << answer << '\n';

	FOR(ll, row, 0, n - 1){
		FOR(ll, col, 0, n - 1){
			ll need = n * (row + col) - row * col;
			ll remain = n * n - need;
			// cerr << row << ' ' << col << ' ' << need << ' ' << remain << '\n';
			
			ll chooseRow = math.C(n, row);
			ll chooseCol = math.C(n, col);

			ll choiceNeed = math.pow(k - 1, need);
			ll choiceRemain = math.pow(k, remain);

			ll allChoose = (chooseCol * chooseRow) % MOD;
			ll choice = (choiceNeed * choiceRemain) % MOD;

			ll curr = (allChoose * choice) % MOD;
			// cerr << "//" << allChoose << ' ' << choice << '\n';
			if (((row + col) & 1)) curr = MOD - curr;
			answer += curr, answer %= MOD;
		}
	}
	answer += MOD - math.pow(k - 1, n * n); answer %= MOD;
	cout << answer;
}