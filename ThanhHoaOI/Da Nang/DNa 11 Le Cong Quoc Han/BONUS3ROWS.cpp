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

const int Up = 1;
const int Down = 0;

int n, query;
int a[5][limit];
ll dist[5][limit];
bool visit[5][limit];
ll f[2][4][4][limit];

bool inside(int x, int y) {
    return (x > 0 && x <= 3 && y > 0 && y <= n);
}

void sub1() {
    queue <pii> q1, q2;
    vpii temp;

    while (query--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        REP(i, 1, 3) REP(j, 1, n) dist[i][j] = minN, visit[i][j] = false;
        dist[x1][y1] = a[x1][y1];
        visit[x1][y1] = true;

        q1.push({x1, y1});
        while (!q1.empty()) {
            while (!q1.empty()) {q2.push(q1.front()); q1.pop();}

            while (!q2.empty()) {
                pii u = q2.front();
                q2.pop();

                FOR(k, 0, 4) {
                    int x = u.fi + dir[k].fi;
                    int y = u.se + dir[k].se;

                    if (inside(x, y) && !visit[x][y]) {
                        if (dist[x][y] < dist[u.fi][u.se] + a[x][y]) {
                            if (dist[x][y] == minN) temp.pb({x, y});
                            dist[x][y] = dist[u.fi][u.se] + a[x][y];
                        }
                    }
                }
            }

            for (auto it : temp) {
                visit[it.fi][it.se] = true;
                q1.push({it.fi, it.se});
            }

            temp.clear();
        }

        cout << dist[x2][y2] << endl;
    }
}

void full() {
    REP(dir, 0, 1) {
        int l = 1, r = 3;
        if (dir == Down) r = 2;
        else l = 2;

        REP(i, l, r) {
            int sta = i;
            if (dir == Down) {
                f[dir][sta][i][1] = a[i][1];
                f[dir][sta][i + 1][1] = a[i][1] + a[i + 1][1];
                REP(j, 1, n) f[dir][sta][i - 1][j] = minN;

                REP(j, 2, n) {
                    REP(k, i, 3) {
                        f[dir][sta][k][j] = max(f[dir][sta][k - 1][j], f[dir][sta][k][j - 1]) + a[k][j];
                    }
                }
            }

            else {
                f[dir][sta][i][1] = a[i][1];
                f[dir][sta][i - 1][1] = a[i][1] + a[i - 1][1];
                REP(j, 1, n) f[dir][sta][i + 1][j] = minN;

                REP(j, 2, n) {
                    REPD(k, i, 1) {
                        f[dir][sta][k][j] = max(f[dir][sta][k + 1][j], f[dir][sta][k][j - 1]) + a[k][j];
                    }
                }
            }
        }
    }

    while (query--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 <= x2) {
            cout << f[0][x1][x2][y2] - f[0][x1][x1][y1] + a[x1][y1] << endl;
        }

        else if (x1 > x2) {
            cout << f[1][x1][x2][y2] - f[1][x1][x1][y1] + a[x1][y1] << endl;
        }
    }
}

void solveProblem() {
    if (n * query <= 1e6) sub1();
    else full();
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("BONUS3ROWS.inp", "r", stdin);
    freopen("BONUS3ROWS.out", "w", stdin);
    cin >> n >> query;

    REP(i, 1, 3) {
        REP(j, 1, n) {
            cin >> a[i][j];
        }
    }
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

