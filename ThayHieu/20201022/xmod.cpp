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

#define MAX 2000001
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

int n, m;
int rMin[MAX], rMax[MAX];
bool visited[MAX];

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	FOR(int, i, 1, MAX - 1) rMin[i] = rMax[i] = -1;

	cin >> n >> m;
	FOR(int, i, 1, n) {
		int num; cin >> num;
		if (visited[num]) continue;
		visited[num] = true;
		for(int j = num; j < MAX; j += num){
			rMin[j] = 0, rMax[j - 1] = max(rMax[j - 1], num - 1);
		}
	}
	rMin[0] = rMax[0] = 0;
	FOR(int, i, 1, MAX - 1)
		if (rMin[i] == -1)
			rMin[i] = rMin[i - 1] + 1;
	FORR(int, i, MAX - 1, 1)
		rMax[i] = max(rMax[i], rMax[i + 1] - 1);
	
	FOR(int, i, 1, m){
		int num; cin >> num;
		cout << rMin[num] << ' ' << rMax[num] << '\n';
	}
}