#include<bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define ALL(v) (v).begin(), (v).end()
#define IS_INF(x)   (std::isinf(x))
#define IS_NAN(x)   (std::isnan(x))
#define fi   first
#define se   second
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x > y + eps) {
            x = y;
            return true;
        } else return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x + eps < y) {
            x = y;
            return true;
        } else return false;
    }
template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE. DRINK A CUP OF TIGERSUGAR BEFORE READING MY CODE. **/

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

#define DAY  33
#define SIZE 15

int numRow, numCol, dryLimit;
int cloudRow, cloudCol, startRow, startCol, range;
int numDay;
bool fest[DAY][SIZE][SIZE], ok[DAY][SIZE][SIZE];
bool vst[DAY][SIZE][SIZE][MASK(4 * 3)];
pair<int, int> corners[4];
int allOne;
vector<int> rainStates;

void init(void) {
//    numRow = numCol = 4;
//    dryLimit = 6;
//    cloudRow = cloudCol = 2;
//    startRow = startCol = 2;
//    range = 2;

    cin >> numRow >> numCol >> dryLimit;
    cin >> cloudRow >> cloudCol >> startRow >> startCol >> range;
    cin >> numDay;
    if (numDay == 0) exit(EXIT_SUCCESS);

    FOR(k, 1, numDay) FOR(i, 1, numRow) FOR(j, 1, numCol) cin >> fest[k][i][j];

    FOR(k, 1, numDay) FOR(i, 1, numRow - cloudRow + 1) FOR(j, 1, numCol - cloudCol + 1) {
        ok[k][i][j] = true;
        REP(x, cloudRow) REP(y, cloudCol) if (fest[k][i + x][j + y]) ok[k][i][j] = false;
    }

    REP(i, 2) REP(j, 2) {
        int x = i ? numRow - cloudRow + 1 : 1;
        int y = j ? numCol - cloudCol + 1 : 1;
        corners[(i << 1) ^ j] = make_pair(x, y);
    }

    allOne = 0;
    REP(love, 4) allOne = (allOne << 3) ^ 1;

    rainStates.clear();
    FOR(a, 0, dryLimit) FOR(b, 0, dryLimit) FOR(c, 0, dryLimit) FOR(d, 0, dryLimit) {
        int mask = 0;
        mask = (mask << 3) ^ a;
        mask = (mask << 3) ^ b;
        mask = (mask << 3) ^ c;
        mask = (mask << 3) ^ d;
        rainStates.push_back(mask);
    }
}

bool inside(int x, int y) {
    return 1 <= x && x <= numRow - cloudRow + 1 && 1 <= y && y <= numCol - cloudCol + 1;
}

int getRainState(int prev, int row, int col) {
    prev += allOne;
    REP(i, 4) if (corners[i].fi == row && corners[i].se == col) prev &= ~(7 << (3 * i));
    return prev;
}

bool validRainState(int rain) {
    while (rain > 0) {
        if ((rain & 7) > dryLimit) return false;
        rain >>= 3;
    }
    return true;
}

bool process(void) {
    if (!ok[1][startRow][startCol]) return false;
    if (numDay == 1) return true;

    FOR(d, 1, numDay) FOR(i, 1, numRow - cloudRow + 1) FOR(j, 1, numCol - cloudCol + 1)
        memset(vst[d][i][j], false, sizeof vst[d][i][j]);

    vst[1][startRow][startCol][getRainState(0, startRow, startCol)] = true;
    FOR(day, 1, numDay - 1) FOR(row, 1, numRow - cloudRow + 1) FOR(col, 1, numCol - cloudCol + 1)
        if (ok[day][row][col]) FORE(it, rainStates) if (vst[day][row][col][*it]) {
            int rain = *it;

            if (ok[day + 1][row][col]) {
                int newRain = getRainState(rain, row, col);
                if (validRainState(newRain)) {
                  if (day + 1 == numDay) return true;
                  vst[day + 1][row][col][newRain] = true;
                }
            }

            REP(dir, 4) FOR(r, 1, range) {
                int newRow = row + dx[dir] * r;
                int newCol = col + dy[dir] * r;
                if (!inside(newRow, newCol)) break;
                if (!ok[day + 1][newRow][newCol]) continue;

                int newRain = getRainState(rain, newRow, newCol);
                if (validRainState(newRain)) {
                    if (day + 1 == numDay) return true;
                    vst[day + 1][newRow][newCol][newRain] = true;
                }
            }
        }

    return false;
}

int main(void) {
#ifdef ONLINE_JUDGE
    freopen("skwthr.inp", "r", stdin);
    freopen("skwthr.out", "w", stdout);
#endif // ONLINE_JUDGE
    ios::sync_with_stdio(false);

    int t; cin >> t;
    REP(love, t) {
        init();
        cout << (process() ? "1" : "0");
    }
    cout << endl;

    return 0;
}

/*** BUBBLE TEA IS GREAT. MY CODE IS AMAZING :D ***/