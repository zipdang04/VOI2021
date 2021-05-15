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

// call: Flow *flow;
class Flow{
    const ll oo = 1e18;
	struct FEdge{int from, dest, oppo; ll cap;};
	private:
		vector<FEdge> edge;
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
			edge.push_back({u, v, m + 1, c});
			edge.push_back({v, u, m, 0});
			graph[u].push_back(m);
			graph[v].push_back(m + 1);
			m += 2;
		}
 
		ll flow(){
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
};

// call: Match *match;
class Match{
	private:
		int n1, n2;
		vector<vi> edge;
		vi match, visited;
		int currTime;

		bool dfs(int i1){
			if (visited[i1] == currTime) return false;
			visited[i1] = currTime;

			for (int i2: edge[i1])
				if (match[i2] == 0 || dfs(match[i2])){
					match[i2] = i1;
					return true;
				}

			return false;
		}

	public:
		Match();
		Match(int n1, int n2){
			this -> n1 = n1;
			this -> n2 = n2;

			edge = vector<vi>(n1);
		}

		void addRelationship(int u, int v){edge[u].push_back(v);}

		int doIt(){
			match = vi(n2, 0);
			visited = vi(n1, 0);
			
			vi thutu(n1);
			FOR(int, i, 0, n1 - 1) thutu[i] = i;
			random_shuffle(thutu.begin(), thutu.end());

			int answer = 0;
			FOR(int, i, 0, n1 - 1){
				currTime++;
				answer += dfs(thutu[i]);
			}

			return answer;
		}

		vi getConfig(){return match;}
};

// call: Math math;
class Math{
	private:
		ll fact[MAX + 1] = {};
		ll ifac[MAX + 1] = {};
	public:
		Math(){
			fact[0] = 1;
			FOR(ll, i, 1, MAX)
				fact[i] = (fact[i - 1] * i) % MOD;
			ifac[MAX] = pow(fact[MAX], MOD - 2);
			FORR(ll, i, MAX - 1, 0)
				ifac[i] = (ifac[i + 1] * (i + 1)) % MOD;
		}

		ll pow(ll a, ll n){
			if (n == 0) return 1;
			ll ans = pow(a, n >> 1);
			ans *= ans, ans %= MOD;
			if (n & 1) return (ans * a) % MOD;
			return ans;
		}

		ll C(ll n, ll k){
			return (((fact[n] * ifac[k]) % MOD) * ifac[n - k]) % MOD;
		}
		
		ll P(ll n, ll k){
			return (fact[n] * ifac[n - k]) % MOD;
		}
		
		ll factorial(ll n){
			return fact[n];
		}
};
