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

int n, m, k;
bool s[MAX << 1];
int cost[MAX];
int prevFree[MAX], endBlock[MAX];

void init(){
	int tmp = n + 1;
	FORR(int, i, n, 1){
		if (s[i] == true) tmp = i;
		endBlock[i] = tmp;
	}

	tmp = 0;
	FOR(int, i, 1, n){
		prevFree[i] = tmp;
		if (s[i] == false) tmp = i;
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input / init
	cin >> n >> m >> k;
	FOR(int, _, 1, m){
		int num; cin >> num; 
		num++; s[num] = true;
	}
	FOR(int, i, 1, k) cin >> cost[i];
	init();
	//=========================
	//main
	ll answer = INT64_MAX;
	FOR(int, len, 1, k){
		int pos = 1;
		ll totalCost = 0, costPerJump = cost[len];
		bool okay = true;
		
		while (pos <= n){
			if (s[pos]){
				int beg = prevFree[pos];
				if (beg == 0){okay = false; break;}
				if (pos - beg >= len){okay = false; break;}

				pos = beg;
			} 
			pos += len;
			totalCost += costPerJump;
		}	
		
		if (okay)
			answer = min(answer, totalCost);
	}
	//=========================
	if (answer == INT64_MAX) answer = -1;
	cout << answer;
}