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

const ll oo = 1e15;
class EdKarp {
	private:
		ll n, s, t;
		vector<vl> resi;
		vector<vl> graph;
		vl path;
		
		bool bfs(){
			path.clear();
			ll lvl[n] = {}, par[n] = {};

			queue<ll> q;
			q.push(s); lvl[s] = 1;
			bool flag = false;
			while (!q.empty()){
				ll node = q.front(); q.pop();
				ll currLvl = lvl[node];

				for (ll child: graph[node]){
					if (lvl[child]) continue;
					if (!resi[node][child]) continue;

					q.push(child);
					lvl[child] = currLvl + 1;
					par[child] = node;
					
					if (child == t) {flag = true; break;}
				}
			}

			if (!flag) return false;

			ll len = lvl[t]; path.resize(len);
			ll u = t;
			FORR(ll, i, len - 1, 0)
				path[i] = u, u = par[u];
			return true;
		}

	public:
		EdKarp(){}

		EdKarp(ll n, ll s, ll t){
			this -> n = n + 1;
			this -> s = s;
			this -> t = t;

			resi.clear(); graph.clear();
			resi = vector<vl>(n, vl(n, 0));
			graph = vector<vl>(n);
		}

		void addEdge(ll u, ll v, ll c){
			resi[u][v] += c;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		ll flow(){
			ll answer = 0;
			while (bfs()){
				ll bottleNeck = oo, len = path.size();
				FOR(ll, i, 1, len - 1)
					bottleNeck = min(bottleNeck, resi[path[i - 1]][path[i]]);
				
				answer += bottleNeck;
				FOR(ll, i, 1, len - 1){
					ll u = path[i - 1], v = path[i];
					resi[u][v] -= bottleNeck,
					resi[v][u] += bottleNeck;
				}
			}

			return answer;
		}
};

EdKarp *flow;
ll n, m;
ll ss, st;
ll c[MAX];


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n; ss = 0, st = n + 1;
	flow = new EdKarp(st + 1, ss, st);
	FOR(ll, i, 1, n){
		ll cost; cin >> cost;
		c[i] = cost;
		
		if (cost > 0)
			flow -> addEdge(ss, i, cost);
		else
			flow -> addEdge(i, st, -cost);
	}
	
	cin >> m;
	FOR(ll, _, 1, m){
		ll u, v; cin >> u >> v;
		flow -> addEdge(u, v, oo);
	}

	ll total = 0;
	FOR(ll, i, 1, n)
		if (c[i] > 0) total += c[i];

	cout << total - (flow -> flow());
}