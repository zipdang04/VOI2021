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

#define MAX 1000002
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

string s;
int n;
int sub1(){
	int ans = 0;
	FOR(int, mask, 0, (1 << n) - 1){
		int cnt[26] = {};
		FOR(int, i, 0, n - 1)
			if (testBit(mask, i))
				cnt[s[i] - 'a']++;
		bool okay = true;
		FOR(int, i, 0, 25)
			if (cnt[i] > 1) {okay = false; break;}
		ans += okay;
	}
	return ans;
}

int f[1 << 20];
int sub2(){
	FOR(int, i, 0, n - 1){
		int curr = s[i] - 'a';
		FOR(int, mask, 0, (1 << n) - 1){
			// 
		}
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> s; n = s.length();
	if (n <= 20) cout << sub1();
	// 
}