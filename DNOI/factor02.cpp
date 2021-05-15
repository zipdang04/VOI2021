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

ll n;
ll listP[MAX], powP[MAX], pLen = 0;
ll divi[MAX], diviLen = 0;
ll f[6721][6721] = {};


void makeDiv(ll num){
	diviLen = 0;
	FOR(ll, i, 1, num){
		if (i * i > num) break;
		if (num % i) continue;

		divi[++diviLen] = i;
		if (num / i != i)
			divi[++diviLen] = num / i;
	}
}

ll find(ll num){
	ll left = 1, right = diviLen, ans = 0;
	while (left <= right){
		ll mid = (left + right) >> 1;
		ll currNum = divi[mid];
		if (currNum == num) return mid;
		else if (currNum < num) left = mid + 1;
		else right = mid - 1;
	}
}

ll calculate(ll num){
	makeDiv(num); sort(divi + 1, divi + diviLen + 1);
	
	FOR(int, i, 1, diviLen)
		FOR(int, j, 1, diviLen)
			f[i][j] = 0;
	
	FOR(int, i, 1, diviLen) f[1][i] = 1;
	FOR(int, i, 2, diviLen){
		ll currNum = divi[i];
		FOR(int, j, 2, diviLen){
			f[i][j] = f[i][j - 1];
			if (j > i) continue;
			ll divNum = divi[j];
			if (currNum % divNum == 0)
				f[i][j] += f[find(currNum / divNum)][j];
		}
	}
	// FOR(int, i, 1, diviLen) cerr << divi[i] << '|'; cerr << '\n'; 
	// FOR(int, i, 1, diviLen) {
	// 	FOR(int, j, 1, diviLen) cerr << f[i][j] << ' ';
	// 	cerr << '\n';
	// }
	return f[diviLen][diviLen] - 1;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t){
		cin >> n;
		cout << calculate(n) << '\n';
	}
}