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

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
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

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
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

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

struct Edge{int u, v;};
int n, m, k, d;
Edge edge[MAX];
mii c;

#define hash(node, t) ((t) * n + (node))

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    //input
    cin >> n >> m;
    FOR(int, i, 1, m)
        cin >> edge[i].u >> edge[i].v;
    cin >> k;
    FOR(int, i, 1, k){
        int node; cin >> node; c[node]++;
    }
    //=========================
    int l = 1, r = 2 * n, ans = n / 2;
    while (l <= r){
        int mid = (l + r) >> 1;
        int t = mid;

        //build graph
        int superSink = hash(n, t) + 1;
        Dinic myDinic(superSink + 10, hash(1, 0), superSink);

        FOR(int, i, 1, n)
            FOR(int, tim, 0, t - 1)
                myDinic.add_edge(hash(i, tim), hash(i, tim + 1), k);
        FOR(int, i, 1, m){
            int u = edge[i].u, v = edge[i].v;
            FOR(int, tim, 0, t - 1)
                myDinic.add_edge(hash(u, tim), hash(v, tim + 1), 1),
                myDinic.add_edge(hash(v, tim), hash(u, tim + 1), 1);
        }
        for (pii child: c){
            int node = child.fi, cap = child.se;
            myDinic.add_edge(hash(node, t), superSink, cap);
            // myDinic.add_edge(superSink, hash(node, t), cap);
        }

        //=========================

        if (myDinic.flow() == k)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    cout << ans;
}