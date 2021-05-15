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
const ll limit = 3e5 + 5;
const ll limit1 = 1e6 + 5;
const ll limit2 = 1e3 + 5;
//If TLE let's use int instead of ll because it's as slow as your WPM :)))

/*----IMPORTANT THINGS----*/
pii dir[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
//right down left up rightdown leftdown rightup leftup
pii NON = {-1, -1};
/*------------------------*/

struct Edge {
    int u, v, w, id;
};

bool cmp1(const Edge &a, const Edge &b) {
    return (a.w == b.w) ? (a.id > b.id) : (a.w > b.w);
}

bool cmp2(const Edge &a, const Edge &b) {
    return (a.w == b.w) ? (a.id < b.id) : (a.w < b.w);
}

int task, n, m, k, p;
Edge edge[limit], newEdge[limit];
int root[limit];
bool isShop[limit];

int findRoot(int u) {
    return (root[u] < 0) ? u : root[u] = findRoot(root[u]);
}

bool mergeRoot(int u, int v) {
    u = findRoot(u);
    v = findRoot(v);

    if (u == v) return false;
    if (root[u] > root[v]) swap(u, v);

    root[u] += root[v];
    isShop[u] |= isShop[v];
    root[v] = u;
    return true;
}

void solveProblem() {
    REP(i, 1, n) root[i] = -1;

    sort(edge + 1, edge + m + 1, cmp1);
    ll res = 0; vi ans1;
    REP(i, 1, m) {
        int u = edge[i].u, v = edge[i].v;
        if (!mergeRoot(u, v)) {
            res += edge[i].w;
            ans1.pb(edge[i].id);
        }
    }
    sort(all(ans1));

    sort(newEdge + 1, newEdge + p + 1, cmp2);
    vi ans2;
    REP(i, 1, p) {
        int u = newEdge[i].u, v = newEdge[i].v;
        int ancU = findRoot(u), ancV = findRoot(v);

        if (ancU != ancV && (!isShop[ancU] || !isShop[ancV])) {
            mergeRoot(u, v);
            res += newEdge[i].w;
            ans2.pb(newEdge[i].id);
        }
    }

    sort(all(ans2));

    cout << res << endl;
    cout << ans1.size() << endl;
    for (auto it : ans1) cout << it << " "; cout << endl;
    cout << ans2.size() << endl;
    for (auto it : ans2) cout << it << " "; cout << endl;
}

void fastInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

void readInput() {
    freopen("MOJI.inp", "r", stdin);
    freopen("MOJI.out", "w", stdout);

    cin >> task;
    cin >> n >> k;
    REP(i, 1, k) {
        int shop;
        cin >> shop;
        isShop[shop] = true;
    }

    cin >> m;
    REP(i, 1, m) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].id = i;
    }

    cin >> p;
    REP(i, 1, p) {
        cin >> newEdge[i].u >> newEdge[i].v >> newEdge[i].w;
        newEdge[i].id = i;
    }
}

int main() {
    fastInput();
    readInput();
    solveProblem();
}

/*
1
13
2
1 11
11
1 2 1
2 4 1
4 1 1
2 3 1
5 6 4
6 7 4
8 9 1
9 10 1
11 12 1
12 13 1
9 12 1
3
3 6 5
7 9 3
4 5 2

1
6
1
5
0
7
2 6 1
1 2 2
5 6 3
1 5 4
3 4 5
4 5 6
3 5 7

1
6
1
5
7
2 6 1
1 2 2
5 6 3
1 5 4
3 4 5
4 5 6
3 5 7
0
*/
