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
	int node, id;
	Node() {node = id = 0;}
	Node(int node, int id) {this -> node = node, this -> id = id;}
};
typedef vector<Node> vg;

#define MAX 5000
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

vector<Node> graph[MAX];
int n, m;
int num[MAX] = {}, low[MAX] = {};
int thoiGian = 0, Cau = 0;

bool usedId[MAX] = {};
void tarjan(int node){
    num[node] = low[node] = ++thoiGian;
    for (Node child: graph[node])
    {
        if (usedId[child.id]) continue;
        usedId[child.id] = true;

        if (num[child.node]) low[node] = min(low[node], num[child.node]);
        else {
            tarjan(child.node);
            low[node] = min(low[node], low[child.node]);
            //
            if (num[node] < low[child.node]) Cau++;
        }
        //
    }
}

vi scc[MAX];
int lvl[MAX] = {};

bool save[MAX][MAX] = {};
void dfs(int node, int parent){
    cerr << "dfs:" << node << ' ' << parent << '\n';
    lvl[node] = lvl[parent] + 1;
    for (int child: scc[node]){
        if (child == parent) continue;
        dfs(child, node);
    }
}
ll process(ll id){
    FOR(int, i, 1, n) if (!num[i]) tarjan(i);
    FOR(int, i,1, n) cerr << num[i] << ' '; cerr << '\n';
    FOR(int, i,1, n) cerr << low[i] << ' '; cerr << '\n';
    FOR(int, node, 1, n){
        int pNode = low[node];
        for (Node child: graph[node]){
            int pChild = low[child.node];
            if (id == child.id) continue;
            if (pNode == pChild) continue;
            if (save[pNode][pChild]) continue;
            save[pNode][pChild] = save[pChild][pNode] = true;
            cerr << pNode << '-' << pChild << '\n';
            scc[pNode].push_back(pChild);
            scc[pChild].push_back(pNode);
        }
    }
    cerr << "done\n";

    int p1 = low[1], p2 = low[2];
    if (p1 == p2) return m - 1;
    dfs(p1, p1);
    cerr << "done dfs\n";
    
    FOR(int, node, 1, n){
        scc[node].clear();

        int pNode = low[node];
        for (Node child: graph[node])
            save[pNode][low[child.node]] = 0;
    }
    if (lvl[p2] == 0) return 0;
    return m - (lvl[p2] - lvl[p1]);
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    
	cin >> n >> m;
    FOR(int, _, 1, m){
        int u, v; cin >> u >> v;
        graph[u].push_back({v, _});
        graph[v].push_back({u, _});
    }

    ll answer = 0;
    FOR(int, i, 1, m){
        cerr << "eliminate:" << i << '\n';
        memset(usedId, 0, sizeof(usedId));
        memset(num, 0, sizeof(num));
        memset(low, 0, sizeof(low));
        memset(lvl, 0, sizeof(lvl));
        thoiGian = Cau = 0;

        usedId[i] = true;
        answer += process(i);
    }
	cout << answer;
	
	// cin >> n >> m;
    // for (int i = 0; i < m; i++)
    // {
    //     int u, v; cin >> u >> v;
    //     graph[u].push_back(v);
    //     graph[v].push_back(u);
    // }

    // for (int i = 1; i <= n; i++)
    // {
    //     if (num[i]) continue;
    //     tarjan(i, i);
    // }
    // int ansKhop = 0;
    // for (int i = 1; i <= n; i++)
    // {
    //     // cout << Khop[i];
    //     ansKhop += Khop[i];
    // }
    // // cout << endl;
    // cout << ansKhop << ' ' << Cau;
    
}