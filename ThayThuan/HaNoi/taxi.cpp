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

#define MAX 21
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

int n, total, fullBit;
int f[21][1 << MAX];
int c[MAX][MAX];

int mid[MAX][MAX];
pii trace[MAX][MAX];

bool checkState(int state){
    state >>= 1;
    int msk1 = state & fullBit;
    state >>= n;
    int msk2 = state & fullBit;
    return (msk1 & msk2) == msk2;
}

int cal(int node, int state){
    if (state == 1) return c[0][node];
    int &ans = f[node][state];
    if (ans) return ans;

    ans = INT32_MAX;
    FOR(int, i, 1, total)
        if (testBit(state, i)){
            int msk = flipBit(state, i);
            if (!checkState(msk)) continue;
            
            int val = cal(i, msk) + c[i][node];
            if (val < ans){
                ans = val;
                trace[node][state] = {i, msk};
            }
        }
    return ans;
}

vi run, path;
void tracePath(int start, int finish){
    while (start != finish){
        start = mid[start][finish];
        path.push_back(start);
    }
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n; 
    n >>= 1;
    fullBit = (1 << n) - 1;
    total = n << 1;
    FOR(int, i, 0, total)
        FOR(int, j, 0, total){ 
            cin >> c[i][j];
        }
    FOR(ll, i, 0, total)
        FOR(ll, j, 0, total)
            mid[i][j] = j;
	FOR(ll, k, 0, total)
        FOR(ll, i, 0, total)
            FOR(ll, j, 0, total)
                if (c[i][k] + c[k][j] < c[i][j]){
                    c[i][j] = c[i][k] + c[k][j];
                    mid[i][j] = mid[i][k];
                }
                
    cout << cal(0, (1 << (total + 1)) - 1) << '\n';
    
    run.push_back(0);
    int node = 0, msk = (1 << (total + 1)) - 1;
    FOR(int, i, 1, 2 * n){
        pii curr = trace[node][msk];
        run.push_back(curr.fi);
        node = curr.fi, msk = curr.se;
    }
    run.push_back(0);
    reverse(run.begin(), run.end());

    path.push_back(0);
    int pre = -1;
    for (int node: run){
        if (pre != -1)
            tracePath(pre, node);
        pre = node;
    }

    cout << path.size() << '\n';
    for (int num: path)
        cout << num << ' ';
}