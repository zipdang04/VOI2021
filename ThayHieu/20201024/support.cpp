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

#define MAX 301
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

Match *match;
int n, m, k;
int dist[MAX][MAX];
int p[MAX], q[MAX];

bool check(int d){
	match = new Match(k + 1, k + 1);
	FOR(int, i, 1, k)
		FOR(int, j, 1, k){
			int n1 = p[i], n2 = q[j];
			if (dist[n1][n2] > d) continue;
			match -> addRelationship(i, j);
		}
	bool okay = (match -> doIt()) == k;
	delete match;
	return okay;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//init
	FOR(int, i, 1, MAX - 1)
		FOR(int, j, 1, MAX - 1)
			dist[i][j] = oo;
	FOR(int, i, 1, MAX - 1) dist[i][i] = 0;
	
	//=========================
	//input
	cin >> n >> m >> k;
	FOR(int, i, 1, m){
		int u, v, w; cin >> u >> v >> w;
		dist[u][v] = dist[v][u] = w;
	}
	FOR(int, i, 1, k) cin >> p[i];
	FOR(int, i, 1, k) cin >> q[i];
	//=========================
	//floyd
	FOR(int, x, 1, n)
		FOR(int, i, 1, n)
			FOR(int, j, 1, n){
				dist[i][j] = min(dist[i][j], dist[i][x] + dist[x][j]);
			}
	//=========================
	//bs the answer
	int left = 0, right = oo, ans = oo;
	while (left <= right){
		int mid = (left + right) >> 1;
		if (check(mid)) ans = mid, right = mid - 1;
		else left = mid + 1;
	}
	//=========================
	cout << ans << '\n';
}