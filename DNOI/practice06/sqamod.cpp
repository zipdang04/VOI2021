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

#define MAX 10001
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

int f[MAX][10][3] = {};
string s;
int dig[MAX];
void init(){
	FOR(int, d, 0, 9)
		f[0][d][(d * d) % 3] = 1;
	FOR(int, pos, 1, MAX - 1)
		FOR(int, currD, 0, 9){
			int r = currD * currD % 3;
			FOR(int, sum, 0, 2){
				int prevSum = (sum + 3 - r) % 3;
				FOR(int, prevD, 0, 9)
					f[pos][currD][sum] += f[pos - 1][prevD][prevSum],
					f[pos][currD][sum] %= MOD;
			}
		}
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	init();
	cin >> s; int len = s.length();
	FOR(int, i, 0, len - 1)
		dig[i] = s[len - i - 1] - '0';
	

	int answer = 0, r = 0;
	FORR(int, pos, MAX - 1, 0){
		int currD = dig[pos];

		FOR(int, prevD, 0, currD - 1)
			answer += f[pos][prevD][r],
			answer %= MOD;
		
		r = (r + 3 - (currD * currD) % 3) % 3;
	}
	cout << answer;
}