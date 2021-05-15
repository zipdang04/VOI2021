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

ll n, r;
ll a[MAX], sum[MAX];
ll f[MAX][2] = {};
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    FOR(int, _, 1, t){
        cin >> n >> r;
        FOR(int, i,1, n){
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
        }
        FOR(int, i, 0, n) f[i][0] = f[i][1] = INT64_MIN;
        if (n <= r) {
            cout << sum[n] << '\n';
            continue;
        }

        f[r + 1][1] = sum[r + 1];
        FOR(int, i, r + 2, n){
            f[i][0] = max(f[i - 1][0], f[i - 1][1]);
            
            f[i][1] = f[i - 1][1] + a[i];
            if (i < n){
                int endPos = max(1ll, i - 2 * r);
                f[i][1] = max(f[i][1], max(0ll, f[endPos - 1][0]) + (sum[i] - sum[endPos - 1]));
            } else {
                FORR(int, endPos, i - r, i - 2 * r){
                    if (endPos < 1) break;
                    // cerr << i << ' ' << endPos << '\n';
                    f[i][1] = max(f[i][1], max(0ll, f[endPos - 1][0]) + (sum[i] - sum[endPos - 1]));
                }
            }
        }
        cout << max(f[n][0], f[n][1]) << '\n';
    }
}