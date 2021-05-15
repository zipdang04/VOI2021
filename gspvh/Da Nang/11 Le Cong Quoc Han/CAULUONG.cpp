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
const ll MOD1 = 1e9 + 7;
const ll MOD = 998244353;
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

int task, n, m;
pair <pii, int> edge[limit];
vpii g[limit], backward[limit];
int dist[1505][1505];
int cnt[1505][1505];
int realDist[1505][1505];
int tmp[1505][1505];
int ans[1505];
int par[1505];

void dijkstra(int sta, int dist[], int cnt[], int type) {
    priority_queue <pii, vpii, greater <pii>> heap;

    REP(i, 1, n) dist[i] = INF, cnt[i] = 0;
    dist[sta] = 0;
    cnt[sta] = 1;
    heap.push({dist[sta], sta});

    while (!heap.empty()) {
        int u = heap.top().se;
        int curDist = heap.top().fi;
        heap.pop();

        if (type == 0) {
            for (auto it : backward[u]) {
                int v = it.fi, w = it.se;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u];
                    heap.push({dist[v], v});
                }

                else if (dist[v] == dist[u] + w) (cnt[v] += cnt[u]) %= MOD;
            }
        }

        else {
            for (auto it : g[u]) {
                int v = it.fi, w = it.se;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    cnt[v] = cnt[u];
                    heap.push({dist[v], v});
                }

                else if (dist[v] == dist[u] + w) (cnt[v] += cnt[u]) %= MOD;
            }
        }
    }
}

void sub3() {
    REP(i, 1, n) dijkstra(i, realDist[i], tmp[i], 1);

    REP(i, 1, m) {
        int u = edge[i].fi.fi, v = edge[i].fi.se, w = edge[i].se;
        dijkstra(u, dist[u], cnt[u], 0);
        dijkstra(v, dist[v], cnt[v], 1);

        int ans = 0;
        REP(j, 1, n) {
            REP(k, 1, n) {
                if (j == k) continue;
                if (dist[u][j] + dist[v][k] + w == realDist[j][k]) {
                    ans = (ans + (1LL * cnt[u][j] * cnt[v][k]) % MOD) % MOD;
                }
            }
        }

        cout << ans << endl;
    }
}

void dfs(int u) {
    ans[u] = 1;
    for (auto it : g[u]) {
        int v = it.fi;
        par[v] = u;
        dfs(v);

        ans[u] += ans[v];
        ans[u] %= MOD;
    }
}

void sub2() {
    int root;
    REP(i, 1, n) {
        if (backward[i].size() == 0) {
            root = i;
            dfs(i);
        }
    }

    REP(i, 1, m) {
        cout << ans[edge[i].fi.se] << endl;
    }
}

void solveProblem() {
    if (task == 1 || task == 3) sub3();
    else if (task == 2) sub2();
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("CAULUONG.inp", "r", stdin);
    freopen("CAULUONG.out", "w", stdout);

    cin >> task;
    cin >> n >> m;

    REP(i, 1, m) {
        cin >> edge[i].fi.fi >> edge[i].fi.se >> edge[i].se;
        g[edge[i].fi.fi].pb({edge[i].fi.se, edge[i].se});
        backward[edge[i].fi.se].pb({edge[i].fi.fi, edge[i].se});
    }
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

/*
1
4 4
1 2 22
2 3 7
3 4 19
1 4 97

1
3 4
1 2 1
1 2 1
2 3 2
2 3 2

2
6 5
1 2 1
1 3 1
2 4 1
2 5 1
3 6 1
*/
