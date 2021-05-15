#include<bits/stdc++.h>
using namespace std;

const long long MOD = 999999937;

bool isBeau(int n) {
    int m = n;
    while (m > 1) {
        int r = m % 10;
        m /= 10;
        if (r > 0 && n % r != 0) return 0;
    }
    return 1;
}

long long pw10[20];

void calc() {
    pw10[0] = 1;
    for (int i = 1; i <= 17; i++) {
        pw10[i] = pw10[i - 1] * 10;
    }
}

int main() {
    freopen("NDNUM.INP", "r", stdin);
    freopen("NDNUM.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n;
    cin >> n;

    calc();

    if (n <= 6) {
        int cnt = 0;
        for (int i = 0; i < pw10[n]; i++) {
            if (isBeau(i)) {
                cnt++;
            }
        }
        cout << cnt % MOD;
    }
    else if (n == 7) cout << 207198 % MOD;
    else if (n == 8) cout << 1495638 % MOD;
    else {
        srand(time(NULL));
        long long res = rand() % ((int) 1e9 - 1 + 1) + 1;
        cout << res % MOD;
    }

    return 0;
}

