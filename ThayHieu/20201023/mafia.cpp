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
const ll oo = 1e10;
class EdKarp {
	private:
		ll n, s, t;
		vector<vl> exResi;
		vector<vl> resi;
		vector<vl> graph;
		vl path;
		vector<bool> visited;
		
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
			this -> n = n;
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
			exResi = resi;
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

		vl makeCut(){

			bool visited[n] = {};
			queue<ll> q;

			q.push(s); visited[s] = true;
			while (!q.empty()){
				ll node = q.front(); q.pop();
				for (ll child: graph[node])
					if (!visited[child] && resi[node][child])
						q.push(child), visited[child] = true;
			}

			bool isCut[n] = {};
			FOR(int, node, 0, n - 1)
				FOR(int, child, 0, n - 1)
					if (visited[node] && !visited[child] && exResi[node][child])
						isCut[node] = true;
			
			vl ans;
			FOR(int, node, 0, n - 1)
				if (isCut[node]) ans.push_back(node);
			return ans;
		}
};

EdKarp *flow;
ll n, m, s, t;
ll c[MAX];
vl graph[MAX];

#define from(node) (node)
#define to(node) ((node) + n)

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> n >> m >> s >> t;
	FOR(ll, i, 1, n) cin >> c[i];
	for (ll i = 0; i < m; i++)
	{
		ll u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	//=========================
	//init
	flow = new EdKarp(n * 2 + 1, from(s), to(t));
	FOR(ll, node, 1, n) {
		flow -> addEdge(from(node), to(node), c[node]);
		for (int child: graph[node]){
			flow -> addEdge(to(node), from(child), oo);
			flow -> addEdge(to(child), from(node), oo);
		}
	}
	//=========================
	int x = flow -> flow();
	vl cut = flow -> makeCut();

	// cerr << x << '\n';
	for (ll child: cut){
		if (child > n) continue;
		cout << child << ' ';
	}
}