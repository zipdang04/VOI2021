#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long a[500005];

long long pw(long long a, long long n) {
    if (n == 0) return 1;
    long long q = pw(a, n / 2);
    if (n % 2 == 0) return q * q % MOD;
    else return q * q % MOD * a % MOD;
}

void mod(long long &val) {
    val = (val % MOD + MOD) % MOD;
}

long long calc(int n) { // O(n)
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        mod(a[i]);
        res += a[i] * pw(n + 1, i) % MOD;
        mod(res);
    }
    return res;
}

int main() {
    freopen("COVID19.INP", "r", stdin);
    freopen("COVID19.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    int test;
    cin >> test;

    int n, k, q;
    cin >> n >> k >> q;

    memset(a, -1, sizeof(a));

    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        a[x] = 0;
    }

    long long res = calc(n);

    for (int z = 0; z <= q; z++) {
        if (z >= 1) {
            char c;
            int x, y;
            cin >> c >> x >> y;

            if (c == 'D') {
                if (a[x] == -1 && a[y] != -1) {
                    if (test == 2) {
                        res -= a[x] * pw(n + 1, x);
                        mod(res);
                    }

                    a[x] = a[y] + 1;

                    if (test == 2) {
                        res += a[x] * pw(n + 1, x);
                        mod(res);
                    }
                }
                else if (a[x] != -1 && a[y] == -1) {
                    if (test == 2) {
                        res -= a[y] * pw(n + 1, y);
                        mod(res);
                    }

                    a[y] = a[x] + 1;

                    if (test == 2) {
                        res += a[y] * pw(n + 1, y);
                        mod(res);
                    }
                }
                else if (a[x] != -1 && a[y] != -1) {
                    if (a[x] > a[y]) {
                        if (test == 2) {
                            res -= a[x] * pw(n + 1, x);
                            mod(res);
                        }

                        a[x] = a[y] + 1;

                        if (test == 2) {
                            res += a[x] * pw(n + 1, x);
                            mod(res);
                        }
                    }
                    else if (a[x] < a[y]) {
                        if (test == 2) {
                            res -= a[y] * pw(n + 1, y);
                            mod(res);
                        }

                        a[y] = a[x] + 1;

                        if (test == 2) {
                            res += a[y] * pw(n + 1, y);
                            mod(res);
                        }
                    }
                }
            }
            else if (test >= 3) {
                long long minVal = 1e18;
                for (int i = x; i <= y; i++) {
                    if (a[i] > -1) {
                        minVal = min(a[i], minVal);
                    }
                }

                for (int i = x; i <= y; i++) {
                    if (a[i] > minVal) a[i] = minVal + 1;
                }
            }
        }

        if (test == 1) cout << res << "\n";
        else if (test == 2) {
            cout << res << "\n";
        }
        else if (test == 3) {
            res = calc(n);
            cout << res << "\n";
        }
    }


    return 0;
} 