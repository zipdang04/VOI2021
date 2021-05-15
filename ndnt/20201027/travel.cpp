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

struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;

#define MAX 105001
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

const int oo = 1e9;

int n, m;
vg graph[MAX];
int a[MAX], b[MAX], c[MAX];
bool choose[MAX];

void Dijkstra(int *ans, int root){
	
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	ans[root] = 0; pq.push({0, root});
	
	while (!pq.empty()){
		pii curr = pq.top(); pq.pop();
		int node = curr.se, len = curr.fi;
		if (len != ans[node]) continue;

		for (Node child: graph[node]){
			int newLen = len + child.len;
			if (newLen < ans[child.node])
				ans[child.node] = newLen, pq.push({newLen, child.node});
		}
	}
	// cerr << "root: " << root << '\n';
	// FOR(int, i, 1, n) cerr << ans[i] << ' '; cerr << '\n';
}

void nen(int *arr, int len){
	mii save;
	FOR(int, i, 1, len)
		save[arr[i]] = true;
	
	int tmp = 0;
	for (pii i: save){
		save[i.fi] = ++tmp;
	}

	FOR(int, i, 1, len)
		arr[i] = save[arr[i]];
}

struct Data{int a, b, c;};
bool operator == (Data a, Data b){
	if (a.a != b.a) return false;
	if (a.b != b.b) return false;
	if (a.c != b.c) return false;
	return true;
}
bool operator < (Data a, Data b){
	if (a.a < b.a) return true;
	if (a.a > b.a) return false;
	if (a.b < b.b) return true;
	if (a.b > b.b) return false;
	return a.c < b.c;
}
Data dat[MAX];

int bit[MAX];
void update(int ind, int val){
	while (ind < MAX)
		bit[ind] = min(bit[ind], val), ind += ind & -ind;
}
int get(int ind){
	int ans = oo;
	while (ind)
		ans = min(bit[ind], ans), ind -= ind & -ind;
	return ans;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, _, 1, m){
		int u, v, w; cin >> u >> v >> w;
		u++, v++;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
	FOR(int, i, 1, MAX - 1) a[i] = b[i] = c[i] = bit[i] = oo;

	Dijkstra(a, 1); nen(a, n);
	Dijkstra(b, 2); nen(b, n);
	Dijkstra(c, 3); nen(c, n);
	// FOR(int, i, 1, n) cerr << a[i] << ' '<< b[i] << ' ' << c[i] << '\n';

	FOR(int, i, 1, n)
		dat[i] = {a[i], b[i], c[i]};

	sort(dat + 1, dat + 1 + n);
	int answer = 0;
	FOR(int, i, 1, n){
		Data curr = dat[i];
		if (curr == dat[i - 1]) {answer += choose[i - 1]; continue;}
		if (get(curr.b) > curr.c)
			answer++, choose[i] = true;
		update(curr.b, curr.c);
	}
	cout << answer;
}