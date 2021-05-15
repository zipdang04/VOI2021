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


int a, b, k;

int f[10][10][100][100]; //pos, digit, mod, summod
int p10[10];

void init(){
	p10[0] = 1;
	FOR(int, i, 1, 9)
		p10[i] = (p10[i - 1] * 10) % k;
	
	FOR(int, d, 0, 9)
		f[0][d][d % k][d % k] = 1;
	
	FOR(int, pos, 1, 9)
		FOR(int, currD, 0, 9){
			int currMod = (currD * p10[pos]) % k, currVal = currD % k;
			FOR(int, mod, 0, k - 1)
				FOR(int, sumMod, 0, k - 1){
					FOR(int, prevD, 0, 9){
						f[pos][currD][mod][sumMod] += f[pos - 1][prevD][(mod + k - currMod) % k][(sumMod + k - currVal) % k];
					}
				}
		}
}

int get(int num){
	int dig[9] = {};
	FOR(int, i, 0, 8)
		dig[i] = num % 10, num /= 10;
	
	int answer = 0; int currMod = 0, currSum = 0;
	FORR(int, pos, 8, 0){
		int currD = dig[pos];

		FOR(int, prevD, 0, currD - 1)
			answer += f[pos][prevD][currMod][currSum];
		
		currMod += k - (currD * p10[pos]) % k, currMod %= k;
		currSum += k - currD % k, currSum %= k;
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
	cin >> a >> b >> k;
	if (k >= 90){cout << 0; return 0;}
	init();
	cout << get(b + 1) - get(a);
}