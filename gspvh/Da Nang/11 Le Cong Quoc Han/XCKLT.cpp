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

struct Trace {
    int preA, preB, preC;
};

string a, b, c;

void sub1() {
    if (a[0] == c[0] || b[0] == c[0]) cout << "TRETRAU" << endl;
    else if (a[0] != b[0]) cout << 2 << endl << a << b << endl;
    else cout << 1 << endl << a << endl;
}

void sub3() {
    //f[i][j][k]: shortest string end at i at string a, j at string b, has k character c;
    vector <vector <vi>> f;
    vector <vector <vector <Trace>>> trace;

    int n = a.size(), m = b.size(), p = c.size() - 1;
    a = '#' + a + 'a';
    b = '#' + b + 'a';
    f.resize(a.size() + 1);
    trace.resize(a.size() + 1);

    REP(i, 0, a.size()) {
        f[i].resize(b.size() + 1);
        trace[i].resize(b.size() + 1);

        REP(j, 0, b.size()) {
            f[i][j].resize(c.size() + 1);
            trace[i][j].resize(c.size() + 1);
        }
    }



    REP(i, 0, a.size()) REP(j, 0, b.size()) REP(k, 0, c.size()) f[i][j][k] = INF;
    f[0][0][0] = 0;

    REP(i, 0, n) {
        REP(j, 0, m) {
            REP(k, 0, p) {
                if (f[i][j][k] == INF) continue;

                if (a[i + 1] == b[j + 1]) {
                    int nxt = k + (a[i + 1] == c[0]);
                    if (f[i + 1][j + 1][nxt] > f[i][j][k] + 1) {
                        f[i + 1][j + 1][nxt] = f[i][j][k] + 1;
                        trace[i + 1][j + 1][nxt] = {i, j, k};
                    }
                }

                else {
                    int nxt = k + (a[i + 1] == c[0]);
                    if (f[i + 1][j][nxt] > f[i][j][k] + 1) {
                        f[i + 1][j][nxt] = f[i][j][k] + 1;
                        trace[i + 1][j][nxt] = {i, j, k};
                    }

                    nxt = k + (b[j + 1] == c[0]);
//                    if (i == 2 && j == 5 && k == 1) cout << nxt << endl;

                    if (f[i][j + 1][nxt] > f[i][j][k] + 1) {
                        f[i][j + 1][nxt] = f[i][j][k] + 1;
                        trace[i][j + 1][nxt] = {i, j, k};
                    }
                }

//                cout << i << " " << j << " " << k << " " << f[i][j][k] << endl;
            }
        }
    }

    int ans = INF;
    int curA, curB, curC;
    REPD(k, c.size() - 1, 0) if (f[n][m][k] != INF) {
        if (ans > f[n][m][k]) {
            ans = f[n][m][k];
            curA = n;
            curB = m;
            curC = k;
        }
    }
    if (ans == INF) {cout << "TRETRAU" << endl; return;}

    string res = "";
    while (curA != 0 || curB != 0) {
        int t1 = curA, t2 = curB, t3 = curC;
        if (trace[t1][t2][t3].preA == t1 - 1) res += a[t1];
        else if (trace[t1][t2][t3].preB == t2 - 1) res += b[t2];

        curA = trace[t1][t2][t3].preA;
        curB = trace[t1][t2][t3].preB;
        curC = trace[t1][t2][t3].preC;
    }

    reverse(all(res));

    cout << ans << endl;
    cout << res << endl;
}

void sub4() {
    //f[i][j][k]: shortest string end at i at string a, j at string b, has k character c;
    vector <vector <vi>> f;
    vector <vector <vector <Trace>>> trace;

    int n = a.size(), m = b.size(), p = c.size() - 1;
    c = '#' + c;
    a = '#' + a + 'a';
    b = '#' + b + 'a';
    f.resize(a.size() + 1);
    trace.resize(a.size() + 1);

    REP(i, 0, a.size()) {
        f[i].resize(b.size() + 1);
        trace[i].resize(b.size() + 1);

        REP(j, 0, b.size()) {
            f[i][j].resize(c.size() + 1);
            trace[i][j].resize(c.size() + 1);
        }
    }



    REP(i, 0, a.size()) REP(j, 0, b.size()) REP(k, 0, c.size()) f[i][j][k] = INF;
    f[0][0][0] = 0;

    REP(i, 0, n) {
        REP(j, 0, m) {
            REP(k, 0, p) {
                if (f[i][j][k] == INF) continue;

                if (a[i + 1] == b[j + 1]) {
                    int nxt = k + (a[i + 1] == c[k + 1]);
                    if (f[i + 1][j + 1][nxt] > f[i][j][k] + 1) {
                        f[i + 1][j + 1][nxt] = f[i][j][k] + 1;
                        trace[i + 1][j + 1][nxt] = {i, j, k};
                    }
                }

                else {
                    int nxt = k + (a[i + 1] == c[k + 1]);
                    if (f[i + 1][j][nxt] > f[i][j][k] + 1) {
                        f[i + 1][j][nxt] = f[i][j][k] + 1;
                        trace[i + 1][j][nxt] = {i, j, k};
                    }

                    nxt = k + (b[j + 1] == c[k + 1]);
//                    if (i == 2 && j == 5 && k == 1) cout << nxt << endl;

                    if (f[i][j + 1][nxt] > f[i][j][k] + 1) {
                        f[i][j + 1][nxt] = f[i][j][k] + 1;
                        trace[i][j + 1][nxt] = {i, j, k};
                    }
                }

//                cout << i << " " << j << " " << k << " " << f[i][j][k] << endl;
            }
        }
    }

    int ans = INF;
    int curA, curB, curC;
    REPD(k, c.size() - 1, 0) if (f[n][m][k] != INF) {
        if (ans > f[n][m][k]) {
            ans = f[n][m][k];
            curA = n;
            curB = m;
            curC = k;
        }
    }
    if (ans == INF) {cout << "TRETRAU" << endl; return;}

    string res = "";
    while (curA != 0 || curB != 0) {
        int t1 = curA, t2 = curB, t3 = curC;
        if (trace[t1][t2][t3].preA == t1 - 1) res += a[t1];
        else if (trace[t1][t2][t3].preB == t2 - 1) res += b[t2];

        curA = trace[t1][t2][t3].preA;
        curB = trace[t1][t2][t3].preB;
        curC = trace[t1][t2][t3].preC;
    }

    reverse(all(res));

    cout << ans << endl;
    cout << res << endl;
}

void solveProblem() {
    bool ok = true;
    FOR(i, 1, c.size()) if (c[i] != c[i - 1]) ok = false;

    if (a.size() == 1 && b.size() == 1 && c.size() == 1) sub1();
    else if (ok) sub3();
    else sub4();
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("XCKLT.inp", "r", stdin);
    freopen("XCKLT.out", "w", stdout);

    cin >> a >> b >> c;
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

/*
bichphuong
vanloi
ii
*/
