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
const ll MOD = 999999937;
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

int n;
ll cur = 0;
ll ans = 0;
ll lcmArr[limit];

int getBit(int msk, int k) {
    return (msk >> k) & 1;
}

int onBit(int msk, int k) {
    return msk | (1 << k);
}

void backtrack(int i, int msk) {
    if (i != 1 && cur % lcmArr[msk] == 0) ++ans;
    if (i > n) return;

    int l = (i == 1) ? 1 : 0;
    REP(j, l, 9) {
        cur *= 10;
        cur += j;
        int newMsk = msk; if (j != 0) newMsk = onBit(msk, j - 1);
        backtrack(i + 1, newMsk);
        cur /= 10;
    }
}

void solveProblem() {
    FOR(msk, 1, (1 << 9)) {
        lcmArr[msk] = 1;
        FOR(j, 0, 9) {
            if (getBit(msk, j)) lcmArr[msk] = (lcmArr[msk] * (j + 1)) / __gcd(lcmArr[msk], (ll)j + 1);
        }
    }

    backtrack(1, 0);
    cout << (ans + 1) % MOD << endl;
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("NDNUM.inp", "r", stdin);
    freopen("NDNUM.out", "w", stdout);

    cin >> n;
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

