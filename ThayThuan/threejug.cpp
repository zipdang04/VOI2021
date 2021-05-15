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

int A, B, C, a, b, c, d, T;
void print(int ans){
	cout << ans; exit(0);
}

int xuly(){
	if (T % d == a % d && T <= A){
		if (T < a){
			int del = (a - T) / d;
			int dB = (B - b) / d;
			int dC = (C - c) / d;
			if (del <= dB + dC) return del;
			else return INT32_MAX;
		} else {
			int need = (T - a) / d;
			int dB = b / d;
			int dC = c / d;
			if (need <= dB + dC) return need;
			else return INT32_MAX;
		}
	} else return INT32_MAX;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> A >> B >> C >> a >> b >> c >> d >> T;
	if (T == a) print(0);
	if (T == b) print(0);
	if (T == c) print(0);
	int ans = xuly();
	swap(A, B), swap(a, b);
	ans = min(ans, xuly());
	swap(A, C); swap(a, c);
	ans = min(ans, xuly());
	if (ans == INT32_MAX) print(-1);
	else print(ans);
}
