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

#define MAX 105
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

struct FlowEdge {
    int v, u;
    ll cap, flow = 0;
    FlowEdge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const ll flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    int add_edge(int v, int u, ll cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        int pos = m;
		adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
		return pos;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, ll pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll flow() {
        ll f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
int m, n;
int w[MAX], h[MAX];
int l[MAX][MAX], r[MAX][MAX];

#define grid(x, y) ((x - 1) * n + (y)) 	//findPos on grid
#define gIn(x, y) grid(x, y) 			//get inNode on flow
#define gOut(x, y) (grid(x, y) + m * n) //get outNode in flow
#define row(x) (2 * m * n + x)			//get row on flow
#define col(y) (2 * m * n + m + y)		//get col on flow
#define SS 0							//supersource on flow
#define ST 20300						//supersink on flow

Dinic flow(ST + 10, SS, ST);
struct Square{int row, col, pos;};
vector<Square> save;
void buildGraph(){
	FOR(int, i, 1, m){
		flow.add_edge(SS, row(i), w[i]);
	}
	FOR(int, i, 1, n){
		flow.add_edge(col(i), ST, h[i]);
	}
	FOR(int, i, 1, m)
		FOR(int, j, 1, n){
			flow.add_edge(row(i), gIn(i, j), w[i]);
			flow.add_edge(gOut(i, j), col(j), h[j]);
			
			int pos = flow.add_edge(gIn(i, j), gOut(i, j), r[i][j]);
			save.push_back({i, j, pos});
		}
}

int ans[MAX][MAX];
void makeGrid(){
	for (Square i: save){
		int row = i.row, col = i.col, pos = i.pos;
		FlowEdge curr = flow.edges[pos];
		ans[row][col] = curr.flow;
	}
}
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	//input
	cin >> m >> n;
	FOR(int, i, 1, m) cin >> w[i];
	FOR(int, i, 1, n) cin >> h[i];
	FOR(int, i, 1, m)
		FOR(int, j, 1, n)
			cin >> l[i][j];
	FOR(int, i, 1, m)
		FOR(int, j, 1, n)
			cin >> r[i][j];
	//========================= 
	//init
	FOR(int, i, 1, m)
		FOR(int, j, 1, n)
			r[i][j] -= l[i][j], 
			w[i] -= l[i][j],
			h[j] -= l[i][j];
	//=========================
	buildGraph(); flow.flow();
	makeGrid();
	FOR(int, i, 1, m){
		FOR(int, j, 1, n) cout << ans[i][j] + l[i][j] << ' ';
		cout << '\n';
	}
}