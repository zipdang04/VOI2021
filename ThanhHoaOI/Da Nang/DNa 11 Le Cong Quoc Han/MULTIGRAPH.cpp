#include <bits/stdc++.h>
#define fi first
#define se second
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORD(i, a, b) for(int i = (a); i > (b); --i)
#define REPD(i, a, b) for(int i = (a); i >=(b); --i)
#define TR(it, a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define endl '\n'
#define mp make_pair
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define ins insert
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define unmap unordered_map
#define pq priority_queue
#define minEle min_element
#define maxEle max_element
#define lb lower_bound //first pos >= val
#define ub upper_bound // first pos > val
#define bp __builtin_popcount
#define debug(a) cout << a << endl
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair <ll, ll> pll;
typedef pair <int, int> pii;
typedef pair <pii, int> ppi;
typedef pair <int, pii> pip;
typedef pair <ll, ld> pld;
typedef pair <ll, pll> pllp;
typedef pair <pll, ll> ppll;
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <pll> vpll;
typedef vector <pii> vpii;
typedef map <int, int> mii;
typedef map <ll, ll> mll;
typedef string BigNum;

const ll maxN = 1e18;
const ll minN = -1e18;
const int INF = 2e9;
const ll MOD = 1e9 + 7;
const ll MOD1 = 998244353;
const int baseHash = 331;
const int bigNumLength = 5000;
const ld PI = acos(-1);

//Remember limit for IT, etc..., and +1 in limit of any array
const ll limit = 2e5 + 5;
const ll limit1 = 1e6 + 5;
const ll limit2 = 1e3 + 5;
//If TLE let's use int instead of ll because it's as slow as your WPM :)))

/*----IMPORTANT THINGS----*/
pii dir[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
//right down left up rightdown leftdown rightup leftup
pii NON = {-1, -1};
/*------------------------*/

int n, q;
vi g[limit];
ll c[505][505];
ll dist[505][505];
int a[505];

void sub13() {
    REP(i, 1, n - 1) {
        REP(j, i + 1, n) {
            c[i][j] = c[j][i] = 1LL * a[i] * a[j];
        }
    }

    REP(k, 1, n) {
        REP(i, 1, n) {
            REP(j, 1, n) {
                c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
            }
        }
    }

    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            a[u] = v;
            REP(i, 1, n) if (i != u) c[u][i] = c[i][u] = 1LL * a[i] * a[u];

            REP(k, 1, n) {
                REP(i, 1, n) {
                    REP(j, 1, n) {
                        c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
                    }
                }
            }
        }

        else {
            cout << c[u][v] << endl;
        }
    }
}

void full() {
    set <pii> s;
    REP(i, 1, n) s.ins({a[i], i});

    while (q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            s.erase(s.find({a[u], u}));
            a[u] = v;
            s.ins({a[u], u});
        }

        else {
            pii chosen = *s.begin();
            ll ans = min(1LL * a[u] * a[v], 1LL * a[u] * chosen.fi + 1LL * chosen.fi * a[v]);
//            cout << a[u] << " " << a[v] << " " << chosen.se << endl;
            cout << (u == v ? 0 : ans) << endl;
        }
    }
}

void solveProblem() {
    if (n <= 100) sub13();
    else full();
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("MULTIGRAPH.inp", "r", stdin);
    freopen("MULTIGRAPH.out", "w", stdout);

    cin >> n >> q;
    REP(i, 1, n) cin >> a[i];
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

