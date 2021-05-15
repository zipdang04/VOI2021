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

#define MAX 101
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

ll m, n;
ll a[MAX][MAX];
ll odd[MAX][MAX];

#define getSum(arr, r1, r2, c1, c2)(arr[r2][c2] - arr[r1 - 1][c2] - arr[r2][c1 - 1] + arr[r1 - 1][c1 - 1])

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll t; cin >> t;
    FOR(ll, _, 1, t){
        cout << "Test " << _ << ": ";
        cin >> m >> n;
        FOR(ll, i, 1, m)
            FOR(ll, j, 1, n){
                cin >> a[i][j];
                odd[i][j] = a[i][j] & 1;

                a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
                odd[i][j] += odd[i - 1][j] + odd[i][j - 1] - odd[i - 1][j - 1];
            }
        
        ll answer = 0;
        FOR(ll, i1, 1, m)
            FOR(ll, i2, i1, m){
                ll mi = 0;
                FOR(ll, j, 1, n){
                    ll curr = getSum(a, i1, i2, 1, j);
                    if (getSum(odd, i1, i2, j, j)){
                        mi = curr;
                        continue;
                    }

                    answer = max(answer, curr - mi);
                    mi = min(mi, curr);
                }
            }

        if (answer) cout << answer;
        else cout << "impossible";
        if (_ < t) cout << '\n';

        FOR(ll, i, 1, m)
            FOR(ll, j, 1, n) a[i][j] = odd[i][j] = false;
    }
}