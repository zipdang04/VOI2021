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

int n, k, s, m, numeral;
map<string, int> msi;
map<pii, bool> mpb;
bool special[MAX];
int cntSpe[MAX];
vi graph[MAX];

int getNum(string &s){
	int num = msi[s];
	if (num == 0)
		num = ++numeral, msi[s] = numeral;
	return num;
}

priority_queue<pii> pq;

main()
{
	// #ifndef ONLINE_JUDGE
	freopen("specone.inp", "r", stdin);
	freopen("specone.out", "w", stdout);
	// #endif
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k >> s >> m;
	FOR(int, i, 1, s){
		string s; cin >> s;
		int num = getNum(s);

		special[num] = true;
	}
	FOR(int, _, 1, m){
		string s1, s2; cin >> s1 >> s2;
		int u = getNum(s1), v = getNum(s2);
		
		if (u > v) swap(u, v);
		if (mpb[{u, v}]) continue;
		mpb[{u, v}] = true;

		graph[u].push_back(v);
		graph[v].push_back(u);

		if (special[v]) cntSpe[u]++;
		if (special[u]) cntSpe[v]++;
	}
	FOR(int, i, 1, n){
		if (special[i]) continue;
		pq.push({cntSpe[i], i});
	}

	while (!pq.empty()){
		pii curr = pq.top(); pq.pop();
		int talk = curr.fi, node = curr.se;
		if (talk != cntSpe[node]) continue;

		if (talk < k) break;
		special[node] = true;
		for (int child: graph[node]){
			if (special[child]) continue;
			cntSpe[child]++;
			pq.push({cntSpe[child], child});
		}
	}
	vector<string> ans;
	for (pair<string, int> i: msi){
		if (special[i.se]) ans.push_back(i.fi);
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (string i: ans){
		cout << i << ' ';
	}
}