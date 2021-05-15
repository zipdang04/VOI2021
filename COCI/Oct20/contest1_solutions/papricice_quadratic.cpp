#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10, INF = 1e9;
vector<int> e[MAXN];
int sz[MAXN], lo[MAXN], hi[MAXN], tick;

int dfs(int x, int p) {
    lo[x] = tick++;
    sz[x] = 1;
    for (auto y : e[x]) {
        if (y != p) sz[x] += dfs(y, x);
    }
    hi[x] = tick;
    return sz[x];
}

int balance(int a, int b, int c) {
    return max({a, b, c}) - min({a, b, c});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    dfs(1, -1);

    int sol = INF;
    for (int x = 2; x <= n; x++) {
        for (int y = x + 1; y <= n; y++) {
            if (lo[x] < lo[y] && lo[y] < hi[x]) 
                sol = min(sol, balance(sz[y], sz[x] - sz[y], n - sz[x]));
            else if (lo[y] < lo[x] && lo[x] < hi[y])
                sol = min(sol, balance(sz[x], sz[y] - sz[x], n - sz[y]));
            else
                sol = min(sol, balance(sz[x], sz[y], n - sz[x] - sz[y]));
        }
    }

    cout << sol << '\n';

    return 0;
}

