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

#define MAX 200001
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

int n, root;
vi graph[MAX];

int cntCh[MAX];

set<int> s[MAX];
int answer = 0;
int process(int x1, int x2, int x3){
    return max(x1, max(x2, x3)) - min(x1, min(x2, x3));
}
void sack(int node, int parent){
    // cerr << node << '\n';
    cntCh[node]++;
    int bigChild = 0;

    for (int child: graph[node]){
        if (child == parent) continue;
        sack(child, node);

        cntCh[node] += cntCh[child];
        if (cntCh[child] > cntCh[bigChild])
            bigChild = child;
    }
    if (bigChild) swap(s[node], s[bigChild]);
    
    int other = n - cntCh[node], remain = cntCh[node];
    for (int child: graph[node]){
        if (child == parent) continue;
        if (child == bigChild) continue;

        for (int x1: s[child]){
            auto it = upper_bound(s[node].begin(), s[node].end(), x1);
            if (it != s[node].end()){
                int x2 = *it;
                answer = min(answer, process(n - x1 - x2, x1, x2));
            }
            if (it != s[node].begin()){
                it--;
                int x2 = *it;
                answer = min(answer, process(n - x1 - x2, x1, x2));
            }
        }
        s[node].insert(s[child].begin(), s[child].end());
        s[child].clear();
    }
    for (int num: s[node]){
        answer = min(answer, process(other, num, remain - num));
    }
    s[node].insert(cntCh[node]);
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    // #ifndef ONLINE_JUDGE
    // freopen("papricice.inp", "r", stdin);
    // freopen("papricice.out", "w", stdout);
    // #endif
    cin >> n;
    FOR(int, i, 1, n - 1)
    {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // find root
    FOR(int, i, 1, n)
        if (graph[i].size() == 1){
            root = i; break;
        }
    // sack
    answer = n;
    sack(root, root);

    cout << answer;
}