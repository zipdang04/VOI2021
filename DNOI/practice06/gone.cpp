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

int a, b;
int f[10][10][100] = {}; //pos, dig, sum

void init(){
	FOR(int, i, 0, 9)
		f[0][i][i] = 1;
	FOR(int, pos, 1, 8)
		FOR(int, dig, 0, 9)
			FOR(int, sum, dig, 99)
				FOR(int, pre, 0, 9)
					f[pos][dig][sum] += f[pos - 1][pre][sum - dig];
}

int get(int num, int sum){
	int dig[10] = {};
	FOR(int, i, 0, 9) dig[i] = num % 10, num /= 10;

	int answer = 0;
	FORR(int, pos, 9, 0){
		int currD = dig[pos];

		FOR(int, prevD, 0, currD - 1)
			answer += f[pos][prevD][sum];

		sum -= currD;
		if (sum < 0) break;
	}
	return answer;
}

bool isP(int n){
	FOR(int, i, 2, n){
		if (i * i > n) break;
		if (n % i) continue;
		return false;
	}
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	init();
	cin >> a >> b;
	int ans = 0;
	FOR(int, num, 2, 100){
		if (!isP(num)) continue;
		// cerr << num << '|' << get(b + 1, num) << ' ' << get(a, num) << '\n';
		ans += get(b + 1, num) - get(a, num);
	}
	cout << ans;
}