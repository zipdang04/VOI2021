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

struct Aug{ll cost, botNeck;}; 
class MCF{
	struct FEdge{int from, dest, oppo; ll cost, cap;};
	const ll oo = 1e18;
	const Aug NaN = {0, 0};

	private:
		vector<FEdge> edge, initial;
		vector<vi> graph;
		int n, m = 0, s, t;
		vi path;
		vl weight;

		void BellFord(){
			weight.clear();
			weight.resize(n);
			ll bigNode = 0;
			FOR(int, stage, 1, n - 1){
				bool done = true;

				FOR(int, i, 0, m - 1){
					FEdge curr = edge[i];
					int u = curr.from, v = curr.dest, w = curr.cost;
					if (weight[u] + w < weight[v])
						done = false,
						weight[v] = weight[u] + w;
				}
				if (done) break;
			}
		}

		void Johnson(){
			BellFord();
			cerr << "list of w:"; FOR(int, i, 0, n - 1) cerr << weight[i] << ' '; cerr << '\n';

			FOR(int, i, 0, m - 1){
				FEdge &curr = edge[i];
				cerr << curr.from << '/' << curr.dest << " cost:" << curr.cost << ", capa:" << curr.cap << ';';
				curr.cost += (weight[curr.from] - weight[curr.dest]) * (i & 1);
				cerr << "new cost:" << curr.cost << '\n';
			}
		}

		Aug shortestPath(){
			path.clear();
			ll dist[n] = {}; int prev[n] = {};
			
			priority_queue<pii, vector<pii>, greater<pii>> pq;
			FOR(int, i, 0, n - 1) prev[i] = -1, dist[i] = oo;
			dist[s] = 0, pq.push({0, s});
			
			bool found = false;
			while (!pq.empty()){
				pii curr = pq.top(); pq.pop();
				int node = curr.se; ll d = curr.fi;
				
				if (d != dist[node]) continue;
				if (node == t){found = true; break;}

				for (int pos: graph[node]){
					FEdge &now = edge[pos];
					if (!now.cap) continue;
					
					int child = now.dest; ll newLen = dist[node] + now.cost;
					if (newLen < dist[child])
						dist[child] = newLen,
						prev[child] = pos,
						pq.push({child, newLen});
				}
			}
			if (!found) return NaN;
 
			
			ll bottleNeck = oo, cost = 0, u = t;
			while (u != s){
				int pos = prev[u];
				FEdge &curr = edge[pos];
				
				path.push_back(pos);
				bottleNeck = min(bottleNeck, curr.cap);
				cost += curr.cost - weight[curr.from] + weight[curr.dest];

				u = curr.from;
			}
			return {cost, bottleNeck};
		}

	public:
		MCF(int n, int s, int t): n(n), s(s), t(t){
			graph.resize(n);
		}

		void addEdge(int u, int v, ll cost, ll cap){
			initial.push_back({u, v, m + 1, cost, cap});
			initial.push_back({v, u, m, -cost, 0});
			graph[u].push_back(m);
			graph[v].push_back(m + 1);
			m += 2;
		}
 
		Aug flow(){
			edge = initial; Johnson();
			Aug answer = NaN;
			while (true){
				Aug res = shortestPath();
				cerr << res.botNeck << '/' << res.cost << '\n';
				
				if (!res.botNeck) break;
 
				answer.botNeck += res.botNeck;
				answer.cost += res.cost;

				for (int pos: path){
					edge[pos].cap -= res.botNeck;
					edge[edge[pos].oppo].cap += res.botNeck;
				}
			}
			return answer;
		}
};

int n, m, k, s, f;
MCF *mcf;

main(){
	ios_base::sync_with_stdio(); cin.tie(NULL);
	cin >> n >> m >> k >> s >> f;
	mcf = new MCF(n + 1, s, f);
	FOR(int, _, 1, m){
		int u, v, c, d; cin >> u >> v >> c >> d;
		mcf->addEdge(u, v, c, d);
	}

	Aug answer = mcf -> flow();
	cout << answer.cost <<  ' ' << answer.botNeck;

}