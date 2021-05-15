#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10, INF = 1e9;

int n, sz[MAXN];
vector<int> e[MAXN];
set<int> A, B;

int calc_sz(int x, int p) {
    sz[x] = 1;
    for (auto y : e[x]) {
        if (y != p) sz[x] += calc_sz(y, x);
    }
    return sz[x];
}

vector<int> closest(const set<int>& S, int val) {
    vector<int> result;
    auto it = S.upper_bound(val);
    if (it != S.end()) result.push_back(*it);
    if (it != S.begin()) {
        --it;
        result.push_back(*it);
    }
    return result;
}

int balance(int a, int b, int c) {
    return max({a, b, c}) - min({a, b, c});
}

int solve(int x, int p) {
    int sol = INF;

    for (auto other_sz : closest(A, (n + sz[x]) / 2))
        sol = min(sol, balance(sz[x], other_sz - sz[x], n - other_sz));
    for (auto other_sz : closest(B, (n - sz[x]) / 2))
        sol = min(sol, balance(sz[x], other_sz, n - sz[x] - other_sz));

    A.insert(sz[x]);
    for (auto y : e[x]) {
        if (y != p) sol = min(sol, solve(y, x));
    }
    A.erase(sz[x]);
    B.insert(sz[x]);

    return sol;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    calc_sz(1, -1);

    int sol = solve(1, -1);
    cout << sol << '\n';

    return 0;
}

