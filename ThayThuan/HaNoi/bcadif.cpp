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

#define MAX 31
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
int m, n, q;
int k[MAX];
vi teach[MAX];
vi canTeach[MAX];
vi conflict[MAX];

int currT[MAX];
int ans = 0;
void test(int course, priority_queue<pii> initPq){
	if (course > n) return;
	ans = max(ans, course);
	
	priority_queue<pii> pq = initPq;
	while (!pq.empty()){
		pii curr = pq.top(); pq.pop();
		int teacher = curr.se; bool okay = true;
		for (int child: conflict[course])
			if (currT[child] == teacher){
				okay = false; break;
			}
		
		initPq.pop();
		curr.fi--; if (curr.fi) initPq.push(curr);
		
		currT[course] = teacher;
		test(course + 1, initPq);
		
		initPq.pop();
		curr.fi++; initPq.push(curr);
	}
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	FOR(int, i, 1, m){
		cin >> k[i];
		FOR(int, j, 1, k[i]){
			int u; cin >> u;
			teach[i].push_back(u);
			canTeach[u].push_back(i);
		}
	}
	cin >> q;
	FOR(int, i, 1, q);{
		int u, v; cin >> u >> v;
		conflict[u].push_back(v);
		conflict[v].push_back(u);
	}

	priority_queue<pii> pq;
	FOR(int, i, 1, m)
		pq.push({canTeach[i].size(), i});
}