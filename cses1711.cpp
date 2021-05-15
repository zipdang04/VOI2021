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
 
#define MAX 500
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

vi g[MAX];

class Flow{
    const ll oo = 1e18;
	struct FEdge{int from, dest, oppo; ll cap;};
	private:
		vector<FEdge> edge, init;
		vector<vi> graph;
		int n, m = 0, s, t;
		vi path;
 
		ll bfs(){
			path.clear();
			int lvl[n] = {}; int prev[n] = {};
			
			queue<int> q;
			q.push(s); lvl[s] = 1;
			bool flag = false;
			
			while (!q.empty()){
				int node = q.front(); q.pop();
				int currLvl = lvl[node];
 
				for (int pos: graph[node]){
					FEdge child = edge[pos];
					if (lvl[child.dest]) continue;
					if (!child.cap) continue;
 
					q.push(child.dest);
					lvl[child.dest] = currLvl + 1;
					prev[child.dest] = pos;
 
					if (child.dest == t){
						flag = true; break;
					}
				}
				if (flag) break;
			}
 
			if (!flag) return false;
 
			ll len = lvl[t] - 1; path.resize(len);
			ll bottleNeck = oo, u = t;
			FOR(int, i, 0, len - 1){
				int pos = prev[u];
				path[i] = pos,
				bottleNeck = min(bottleNeck, edge[pos].cap);
				u = edge[pos].from;
			}
			return bottleNeck;
		}
 
	public:
		Flow(int n, int s, int t): n(n), s(s), t(t){
			graph.resize(n);
		}
 
		void addEdge(int u, int v, ll c){
			init.push_back({u, v, m + 1, c});
			init.push_back({v, u, m, 0});
			graph[u].push_back(m);
			graph[v].push_back(m + 1);
			m += 2;
		}
 
		ll flow(){
			edge = init;
			ll answer = 0;
			while (true){
				ll bottleNeck = bfs();
				if (!bottleNeck) break;
 
				answer += bottleNeck;
				for (int pos: path){
					edge[pos].cap -= bottleNeck;
					edge[edge[pos].oppo].cap += bottleNeck;
				}
			}
			return answer;
		}

		void buildGraph(){
			FOR(int, node, 0, n - 1){
				for (int pos: graph[node]){
					FEdge curr = edge[pos], old = init[pos];
					
					if (!old.cap) continue;
					if (curr.cap) continue;
					
					g[node].push_back(curr.dest);
				}
			}
		}
};
 
int n, m;
Flow *flow;

void dfs(vi &arr, int node){
	arr.push_back(node);
	for (int &child: g[node]){
		if (child == -1) continue;
		dfs(arr, child);
		child = -1;
		break;
	}
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    flow = new Flow(n + 1, 1, n);
    FOR(int, _, 1, m){
        int u, v; cin >> u >> v;
        flow -> addEdge(u, v, 1);
    }
    cout << flow -> flow() << '\n';
	flow -> buildGraph();
	for (int child: g[1]){
		vi curr; curr.push_back(1);
		dfs(curr, child);
		cout << curr.size() << '\n';
		for (int num: curr)
			cout << num << ' ';
		cout << '\n';
	}
}