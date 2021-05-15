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

#define MAX 1001
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

class EdKarp {
	private:
		const int oo = 1e9+50000;
		int n, s, t;
		vector<vi> resi;
		vector<vi> graph;
		vi path;
		
		bool bfs(){
			path.clear();
			int lvl[n] = {}, par[n] = {};

			queue<int> q;
			q.push(s); lvl[s] = 1;
			bool flag = false;
			while (!q.empty()){
				int node = q.front(); q.pop();
				int currLvl = lvl[node];

				for (int child: graph[node]){
					if (lvl[child]) continue;
					if (!resi[node][child]) continue;

					q.push(child);
					lvl[child] = currLvl + 1;
					par[child] = node;
					
					if (child == t) {flag = true; break;}
				}
			}

			if (!flag) return false;

			int len = lvl[t]; path.resize(len);
			int u = t;
			FORR(int, i, len - 1, 0)
				path[i] = u, u = par[u];
			return true;
		}

	public:
		EdKarp(){}

		EdKarp(int n, int s, int t){
			this -> n = n + 1;
			this -> s = s;
			this -> t = t;

			resi.clear(); graph.clear();
			resi = vector<vi>(n, vi(n, 0));
			graph = vector<vi>(n);
		}

		void addEdge(int u, int v, int c){
			resi[u][v] += c;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		int flow(){
			int answer = 0;
			while (bfs()){
				int bottleNeck = oo, len = path.size();
				FOR(int, i, 1, len - 1)
					bottleNeck = min(bottleNeck, resi[path[i - 1]][path[i]]);
				
				answer += bottleNeck;
				FOR(int, i, 1, len - 1){
					int u = path[i - 1], v = path[i];
					resi[u][v] -= bottleNeck,
					resi[v][u] += bottleNeck;
				}
			}

			return answer;
		}
};

int n, m, s, t;
EdKarp *flow;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> s >> t;
	flow = new EdKarp(n + 1, s, t);
	FOR(int, i, 1, m){
		int u, v, c; cin >> u >> v >> c;
		flow -> addEdge(u, v, c);
	}
	cout << (flow -> flow());
	delete flow;
}