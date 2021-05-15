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

#define ha(x) (x + 100)

int a, b;

int f[9][10][200];

void init(){
	FOR(int, dig, 0, 9)
		f[0][dig][ha(dig)] = 1;
	FOR(int, pos, 1, 8){
		int mul = (pos & 1) ? -1 : 1;
		FOR(int, currD, 0, 9){
			FOR(int, sum, -100, 100){
				int newSum = sum + mul * currD;
				if (newSum < -100 || newSum > 100) continue;
				FOR(int, prevD, 0, 9)
					f[pos][currD][ha(newSum)] += f[pos - 1][prevD][ha(sum)];
			}
		}
	}
}

int get(int num, int sum){
	int dig[9] = {};
	FOR(int, i, 0, 8)
		dig[i] = num % 10, num /= 10;
	
	int answer = 0;
	FORR(int, pos, 8, 0){
		int currD = dig[pos];
		
		FOR(int, prevD, 0, currD - 1)
			answer += f[pos][prevD][ha(sum)];
		
		sum -= ((pos & 1) ? -currD : currD);
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
	ios_base::sync_with_stdio(0); cin.tie(0); init();
	cin >> a >> b;
	int ans = 0;
	FOR(int, i, 2, 81)
		if (isP(i))
			ans += get(b + 1, -i) - get(a, -i);
	cout << ans;
}