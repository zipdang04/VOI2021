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

#define MAX 502
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
//==================================================================
//make data structure
struct Point {int x, y;};
Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}
bool operator == (Point a, Point b){return (a.x == b.x) && (a.y == b.y);}
bool operator != (Point a, Point b){return !(a == b);}
const Point direc[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
const Point NaN = {0, 0};
//==================================================================

int n, w, h;
char maze[MAX][MAX];
Point robot[10];

#define BLOCK 'x'
#define CCW 'A'
#define CW 'C'
Point dest[MAX][MAX][4];
bool check(Point p){return (p.x >= 1) && (p.y >= 1) && (p.x <= w) && (p.y <= h);}
Point run(Point pos, int d){
    Point &ans = dest[pos.x][pos.y][d];
    if (ans != NaN) return ans;

    Point nxt = pos + direc[d];
    char c = maze[nxt.x][nxt.y];
    if (!check(nxt) || c == BLOCK){ans = pos; return pos;}

    if (c == CCW) d = (d + 3) % 4;
    if (c == CW) d = (d + 1) % 4;
    ans = run(nxt, d);
    return ans;
}

const int oo = 100000000;
int f[10][10][MAX][MAX];
void bfs(int x1, int x2, vector<Point> &root, int add){
    queue<Point> q;

    for (Point p: root)
        q.push(p), f[x1][x2][p.x][p.y] = add;
    while (!q.empty()){
        Point curr = q.front(); q.pop();
        int currVal = f[x1][x2][curr.x][curr.y];

        FOR(int, d, 0, 3){
            Point now = dest[curr.x][curr.y][d];
            if (!check(now)) continue;
            if (f[x1][x2][now.x][now.y] <= currVal) continue;

            q.push(now); f[x1][x2][now.x][now.y] = currVal + 1;
        }
    }
}
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    //==================================================================
    //input
    cin >> n >> h >> w;
    FOR(int, i, 1, w) {
        cin >> maze[i] + 1;
        FOR(int, j, 1, h){
            char c = maze[i][j];
            if ('0' <= c && c <= '9')
                robot[c - '0'] = {i, j};
        }
    }
    //==================================================================
    //init
    FOR(int, i, 1, 9)
        FOR(int, j, i, 9)
            FOR(int, row, 1, w)
                FOR(int, col, 1, h)
                    f[i][j][row][col] = oo;
    FOR(int, row, 1, w)
        FOR(int, col, 1, h)
            FOR(int, d, 0, 3)
                run({row, col}, d);
    // cerr << "///\n";
    //==================================================================
    //dp
    FOR(int, i, 1, n){
        Point pos = robot[i];
        vector<Point> root; root.push_back(pos);
        bfs(i, i, root, 0);
    }
    FOR(int, len, 2, n){
        FOR(int, l, 1, n - len + 1){
            int r = l + len - 1;

            int best = oo;
            vector<Point> root;
            FOR(int, mid, l, r - 1){
                FOR(int, row, 1, w)
                    FOR(int, col, 1, h){
                        int x1 = f[l][mid][row][col], x2 = f[mid + 1][r][row][col];
                        if (x1 == -1 || x2 == -1) continue;
                        int cost = x1 + x2;
                        f[l][r][row][col] = min(f[l][r][row][col], cost);
                        if (cost < best){
                            best = cost, root.clear(); root.push_back({row, col});
                        } else if (cost == best)
                            root.push_back({row, col});
                    }
            }
            // cerr << l << ' ' << r << ' ' << best << '\n';
            bfs(l, r, root, best);
        }
    }
    int answer = oo;
    FOR(int, row, 1, w)
        FOR(int, col, 1, h)
            answer = min(answer, f[1][n][row][col]);
    if (answer == oo) answer = -1;
    cout << answer;
    //==================================================================
}