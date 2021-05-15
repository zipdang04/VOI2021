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

#define testBit(n, bit) ((n >> bit) & 1)
#define flipBit(n, bit) (n ^ (1ll << bit))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

ll n;
char s[MAX];
ll p3[MAX];
ll f[MAX][4];
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> s + 1;
	FOR(int, i, 1, n) {
		if (s[i] == '?') s[i] = 0;
		else s[i] -= 'a' - 1;
	}
	
	ll amount = 1;
	FOR(int, i, 1, n){
		if (s[i] == 0){
			f[i][1] = (f[i - 1][1] * 3 + amount) % MOD;
			f[i][2] = (f[i - 1][2] * 3 + f[i - 1][1]) % MOD;
			f[i][3] = (f[i - 1][3] * 3 + f[i - 1][2]) % MOD;
			amount *= 3, amount %= MOD;
		}
		else if (s[i] == 1){
			f[i][1] = (f[i - 1][1] + amount) % MOD;
			f[i][2] = f[i - 1][2];
			f[i][3] = f[i - 1][3];
		}
		else if (s[i] == 2){
			f[i][1] = f[i - 1][1];
			f[i][2] = (f[i - 1][2] + f[i - 1][1]) % MOD;
			f[i][3] = f[i - 1][3];
		}
		else{
			f[i][1] = f[i - 1][1];
			f[i][2] = f[i - 1][2];
			f[i][3] = (f[i - 1][3] + f[i - 1][2]) % MOD;
		}
		// cerr << int(s[i]) << '/' << f[i][1] << ' ' << f[i][2] << ' ' << f[i][3] << '\n';


	}
	cout << f[n][3]; 
}