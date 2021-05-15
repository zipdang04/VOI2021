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

int n, k;
bool camp[limit];
int visit[limit];
vi g[limit];
vi enemy;

void sub1() {
    vector <vector <int>> dist;
    dist.resize(n + 1);
    REP(i, 1, n) dist[i].resize(n + 1);

    queue <int> q;
    for (auto it : enemy) {
        REP(i, 1, n) visit[i] = -1;
        visit[it] = 0;
        ++dist[it][0];
        q.push(it);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto v : g[u]) {
                if (visit[v] == -1) {
                    visit[v] = visit[u] + 1;
                    ++dist[v][visit[v]];
                    q.push(v);
                }
            }
        }
    }

    int ans = 0; vi res;
    REP(i, 1, n) {
        bool ok = true;
        REP(j, 0, n) if (dist[i][j] >= 2) {ok = false; break;}
        if (ok) ++ans, res.pb(i);
    }

    cout << ans << endl;
    for (auto it : res) cout << it << " ";
}

void solveProblem() {
    sub1();
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("MILITARY.inp", "r", stdin);
    freopen("MILITARY.out", "w", stdout);

    cin >> n >> k;
    REP(i, 1, k) {
        int x; cin >> x;
        camp[x] = true;
        enemy.pb(x);
    }

    REP(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}
/*
5 3
1 2 5
5 4
1 5
2 4
5 3
*/
