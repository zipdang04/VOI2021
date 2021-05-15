#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 9
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

struct DSU{
    ll root[MAX];
    
    DSU(){
        FOR(ll, i, 0, MAX - 1)
            root[i] = i;
    }

    void join(ll u, ll v){
        u = root[u], v = root[v];
        if (u == v) return;

        if (u > v) swap(u, v);
        FOR(ll, i, 0, MAX - 1)
            if (root[i] == v) root[i] = u;
    }
};

struct DP{
    ll arr[1][2][3][4][5][6][7][8][9] = {};
    DP(ll value){
        FOR(ll, i0, 0, 0)
        FOR(ll, i1, 0, 1)
        FOR(ll, i2, 0, 2)
        FOR(ll, i3, 0, 3)
        FOR(ll, i4, 0, 4)
        FOR(ll, i5, 0, 5)
        FOR(ll, i6, 0, 6)
        FOR(ll, i7, 0, 7)
        FOR(ll, i8, 0, 8)
            arr[i0][i1][i2][i3][i4][i5][i6][i7][i8] = value;
    }
    ll& operator[](DSU &dsu){
        return arr[dsu.root[0]]
                  [dsu.root[1]]
                  [dsu.root[2]]
                  [dsu.root[3]]
                  [dsu.root[4]]
                  [dsu.root[5]]
                  [dsu.root[6]]
                  [dsu.root[7]]
                  [dsu.root[8]];
    }
};

const ll NaN = -1;
DSU root;
DP f(0), add(NaN);

ll n, m;
queue<DSU> q;
stack<DSU> st;

void upd(ll val, DSU &dsu){
    ll &pos = add[dsu];
    if (pos == NaN)
        st.push(dsu), pos = 0;
    pos += val;
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    f[root] = 1; q.push(root);
    FOR(ll, __, 1, m){
        ll u, v; cin >> u >> v; u--, v--;
        root.join(u, v);
        // cerr << u << ' ' << v << '\n'; 

        while (!q.empty()){
            DSU curr = q.front(); q.pop();
            // // // cerr << "//in : "; FOR(ll, i, 0, n - 1) cerr << curr.root[i] << ' '; cerr << '\n';
            ll num = f[curr]; upd(0, curr);
            
            curr.join(u, v);
            // // // cerr << "//xxx: "; FOR(ll, i, 0, n - 1) cerr << curr.root[i] << ' '; cerr << '\n';
            upd(num, curr);
        }

        while(!st.empty()){
            DSU curr = st.top(); st.pop(); q.push(curr);
            // // // cerr << "//out: "; FOR(ll, i, 0, n - 1) cerr << curr.root[i] << ' '; cerr << '\n';
            ll num = add[curr]; add[curr] = NaN;
            f[curr] += num;
        }
    }
    cout << f[root];
}