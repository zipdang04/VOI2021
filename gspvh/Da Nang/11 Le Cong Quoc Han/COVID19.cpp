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
const ll limit = 5e5 + 5;
const ll limit1 = 1e6 + 5;
const ll limit2 = 1e3 + 5;
//If TLE let's use int instead of ll because it's as slow as your WPM :)))

/*----IMPORTANT THINGS----*/
pii dir[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
//right down left up rightdown leftdown rightup leftup
pii NON = {-1, -1};
/*------------------------*/

int task, n, infect, q;
int infected[limit];
int p[limit];

ll power(ll n, ll k, ll m) {
    if (k == 0) return 1;
    ll t = power(n, k >> 1, m);
    return (k & 1) ? t * t % m * n % m : t * t % m;
}

void sub1() {
    REP(i, 1, q + 1) cout << 0 << endl;
}

void fix(int &ans) {
    if (ans < 0) ans += MOD;
    if (ans >= MOD) ans -= MOD;
}

void sub3() {
    int ans = 0;
    REP(i, 0, n) p[i] = power(n + 1, i, MOD);

    REP(i, 1, n) {
        ans += (1LL * infected[i] * p[i]) % MOD;
        fix(ans);
    }
    cout << ans << endl;

    while (q--) {
        char c; int u, v;
        cin >> c >> u >> v;
        if (c == 'D') {
            if (infected[u] == -1 && infected[v] != -1) infected[u] = infected[v] + 1;
            else if (infected[v] == -1 && infected[u] != -1) infected[v] = infected[u] + 1;
            else if (infected[u] != -1 && infected[v] != -1) {
                int t = min(infected[u], infected[v]) + 1;
                infected[u] = min(infected[u], t);
                infected[v] = min(infected[v], t);
            }
        }

        else if (c == 'P') {
            int cur = INF;
            REP(i, u, v) if (infected[i] != -1) cur = min(cur, infected[i]);
            REP(i, u, v) if ((infected[i] == -1 || infected[i] > cur + 1) && cur != INF) infected[i] = cur + 1;
        }

//        REP(i, 1, n) cout << infected[i] << " "; cout << endl;

        int ans = 0;
        REP(i, 1, n) {
            ans += (1LL * infected[i] * p[i]) % MOD;
            fix(ans);
        }

        cout << ans << endl;
    }
}

void sub2() {
    int ans = 0;
    REP(i, 0, n) p[i] = power(n + 1, i, MOD);

    REP(i, 1, n) {
        ans += (1LL * infected[i] * p[i]) % MOD;
        fix(ans);
    }
    cout << ans << endl;

    while (q--) {
        char c; int u, v;
        cin >> c >> u >> v;

        if (infected[u] == -1 && infected[v] != -1) {
            ans -= (1LL * infected[u] * p[u]) % MOD;
            fix(ans);

            infected[u] = infected[v] + 1;

            ans += (1LL * infected[u] * p[u]) % MOD;
            fix(ans);
        }

        else if (infected[v] == -1 && infected[u] != -1) {
            ans -= (1LL * infected[v] * p[v]) % MOD;
            fix(ans);

            infected[v] = infected[u] + 1;

            ans += (1LL * infected[v] * p[v]) % MOD;
            fix(ans);
        }

        else if (infected[u] != -1 && infected[v] != -1) {
            ans -= (1LL * infected[u] * p[u]) % MOD;
            fix(ans);
            ans -= (1LL * infected[v] * p[v]) % MOD;
            fix(ans);

            int t = min(infected[u], infected[v]) + 1;
            infected[u] = min(infected[u], t);
            infected[v] = min(infected[v], t);

            ans += (1LL * infected[u] * p[u]) % MOD;
            fix(ans);
            ans += (1LL * infected[v] * p[v]) % MOD;
            fix(ans);
        }

        cout << ans << endl;
    }
}

void solveProblem() {
    if (task == 1) sub1();
    else if (task == 3) sub3();
    else if (task == 2) sub2();
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("COVID19.inp", "r", stdin);
    freopen("COVID19.out", "w", stdout);

    cin >> task;
    cin >> n >> infect >> q;

    REP(i, 1, n) infected[i] = -1;
    REP(i, 1, infect) {
        int x;
        cin >> x;
        infected[x] = 0;
    }
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

/*
3
6 2 7
1 3
D 3 4
D 5 6
D 2 4
D 2 6
D 5 6
D 1 2
P 4 6
*/

