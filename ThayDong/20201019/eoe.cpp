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

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	bool x, y; 
	string s; cin >> s; s += '+';
	string sss; 
	cin >> sss; x = (sss == "Odd");
	cin >> sss; y = (sss == "Odd");

	bool odd = false, tmp = false, mul = false, ans = false;
	for (char c: s){
		if (c == '*'){
			if (mul) tmp &= odd;
			else mul = true, tmp = odd;
			odd = false;
		} else if (c == '+' || c == '-'){
			if (mul){
				tmp &= odd;
				ans ^= tmp;
			} else {
				ans ^= odd;
			}
			odd = tmp = mul = false;
		} else if (c == 'x') odd = x;
		else if (c == 'y') odd = y;
		else {
			odd = (c - '0') & 1;
		}
	}
	cout << (ans ? "Odd" : "Even") << '\n';
}