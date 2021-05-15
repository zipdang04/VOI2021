/*
 * Nhận xét: d[i] <= d[i + 1] => t[i] <= t[i + 1];
 * 
 */
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

#define MAX 35
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

const ll NaN = INT64_MAX;

ll m, n;
pll save[MAX];
ll d[MAX];
ll f[MAX][10001];

ll dp(ll pos, ll money){
    ll &ans = f[pos][money];
    if (ans != NaN) return ans;
    if (pos == 1 || money == pos){
        f[pos][money] = 0;
        return 0;
    }
    if (money < pos) return NaN;

    money -= pos;
    ans = min(ans, dp(pos, money));
    
    ll totalD = 0;
    FORR(int, i, pos - 1, 1){
        totalD += d[i + 1];
        ll curr = dp(i, money);
        if (curr == NaN) continue;
        
        curr += totalD * i;
        ans = min(ans, curr);
    }

    return ans;
}

ll mon[MAX] = {};
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> m >> n;
    FOR(int, i, 1, m) {cin >> save[i].fi; save[i].se = i;}
    sort(save + 1, save + 1 + m, greater<pll>());
    FOR(int, i, 1, m) d[i] = save[i].fi;

    FOR(int, i, 0, m)
        FOR(int, j, 0, n)
            f[i][j] = NaN;

    cout << dp(m, n) << '\n';
    int tmp = m;
    while (m){
        if (m == 1){
            mon[m] += n; break;
        }

        mon[m]++;
        if (m == n){break;}
        if (n >= m && f[m][n] == f[m][n - m]){
            n -= m; continue;
        }

        ll totalD = 0;
        FORR(ll, i, m - 1, 1){
            totalD += d[i + 1];
            ll curr = f[i][n - m];
            if (curr == NaN) continue;

            curr += totalD * i;
            if (curr == f[m][n]){
                n -= m, m = i;
                break;
            }
        }
    }
    FORR(int, i, tmp, 1) mon[i] += mon[i + 1];
    // reverse(mon + 1, mon + 1 + tmp);
    FOR(int, i, 1, tmp) d[save[i].se] = mon[i];
    FOR(int, i, 1, tmp) cout << d[i] << ' ';
}