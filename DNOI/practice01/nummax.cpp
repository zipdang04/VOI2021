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

#define MAX 1000005
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

ll n, b;
ll a[MAX];
ll ma = 0;
ll save[MAX], len = 0;
ll answer = 0;
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> b;
	FOR(ll, i, 1, n){
		cin >> a[i];
		ma = max(ma, a[i]);
	}

	a[n + 1] = ma + 1;
	ll cnt = 0;
	FOR(ll, i, 1, n + 1){
		// cerr << i << '/' << a[i] << '\n';
		cnt++;
		if (a[i] == b){
			save[++len] = cnt;
			cnt = 0;
		}
		else if (a[i] > b){
			save[++len] = cnt;
			cnt = 0;
			// cerr << "here" << len << '\n';
			ll sumSq = 0, sqSum = 0;
			FOR(ll, i, 1, len){
				sumSq += save[i] * save[i], sqSum += save[i];
			}
			answer += (sqSum * sqSum - sumSq) / 2;
			len = 0;
		}
	}
	cout << answer << '\n';
}