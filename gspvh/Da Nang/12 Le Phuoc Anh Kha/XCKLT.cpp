#include <bits/stdc++.h>
using namespace std;

long long d[505][505];
pair<int, int> par[505][505];

void sub1(string &a, string &b, string &c) {
    if (a[0] == c[0] || b[0] == c[0]) {
        cout << "TRETRAU";
    }
    else {
        if (a[0] == b[0]) {
            cout << 1 << "\n";
            cout << a;
        }
        else {
            a += b;
            cout << 2 << "\n";
            cout << a;
        }
    }
}

int main() {
    freopen("XCKLT.INP", "r", stdin);
    freopen("XCKLT.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    string a, b, c;
    cin >> a >> b >> c;

    int n = a.size();
    int m = b.size();
    int p = c.size();

    if (n == 1 && m == 1 && p == 1) {
        sub1(a, b, c);
    }
    else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i - 1] == b[j - 1]) {
                    d[i][j] = d[i - 1][j - 1] + 1;
                    par[i][j] = {i - 1, j - 1};
                }
                else {
                    d[i][j] = max(d[i - 1][j], d[i][j - 1]);

                    if (d[i - 1][j] >= d[i][j - 1]) {
                        par[i][j] = {i - 1, j};
                    }
                    else {
                        par[i][j] = {i, j - 1};
                    }
                }
            }
        }

        pair<int, int> trace = {n, m};
        vector<int> id1, id2;

        while (trace.first > 0 && trace.second > 0) {
            if (a[trace.first - 1] == b[trace.second - 1]) {
                id1.push_back(trace.first - 1);
                id2.push_back(trace.second - 1);
            }
            trace = par[trace.first][trace.second];
        }

        reverse(id1.begin(), id1.end());
        id1.push_back(n);
        
        reverse(id2.begin(), id2.end());
        id2.push_back(m);

        string ans;

        int cnt = 0;
        int i = 0, j = 0;
        while (cnt < id1.size()) {
            while (i != id1[cnt] || j != id2[cnt]) {
                if (i != id1[cnt]) {
                    ans += a[i];
                    i++;
                }
                else if (j != id2[cnt]) {
                    ans += b[j];
                    j++;
                }
            }

            if (i == n && j == m) break;

            if (i == id1[cnt] && j == id2[cnt]) {
                ans += a[i];
                i++;
                j++;
            }
            cnt++;
        }

        int id = 0;
        bool ok = true;
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] == c[id]) {
                id++;
            }
            if (id == p) {
                ok = false;
                break;
            }
        }

        if (ok) {
            cout << n + m - d[n][m] << "\n";
            cout << ans;
        }
        else cout << "TRETRAU";
    }


    return 0;
}