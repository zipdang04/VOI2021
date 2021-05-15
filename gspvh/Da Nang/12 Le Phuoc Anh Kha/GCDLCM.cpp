#include <bits/stdc++.h>
using namespace std;

struct Query {
    string type;
    int x, y;
    long long z;

    bool operator < (const Query &other) const {
        return (type == "GCD");
    }
};

long long a[10005];
Query q[10005];

long long lcm(long long a, long long b) {
    long long g = __gcd(a, b);
    return a * b / g;
}

int main() {
    freopen("GCDLCM.INP", "r", stdin);
    freopen("GCDLCM.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    int test, testcase;
    cin >> test >> testcase;

    for (int z = 1; z <= testcase; z++) {
        int n, m;
        cin >> n >> m;

        for (int i = 1; i <= n; i++) {
            a[i] = 1;
        }

        for (int i = 1; i <= m; i++) {
            cin >> q[i].type >> q[i].x >> q[i].y >> q[i].z;
        }

        sort(q + 1, q + m + 1);

        // cout << z << endl;
        for (int i = 1; i <= m; i++) {
            // cout << q[i].type << ' ' << q[i].x << ' ' << q[i].y << ' ' << q[i].z << endl;
        }

        if (test == 2) {
            for (int i = 1; i <= m; i++) {
                a[q[i].x] = lcm(q[i].z, a[q[i].x]);
                a[q[i].y] = lcm(q[i].z, a[q[i].y]);
            }

            bool ok = true;
            for (int i = 1; i <= m; i++) {
                if (__gcd(a[q[i].x], a[q[i].y]) != q[i].z) ok = false;
            } 

            if (ok) cout << "Y";
            else cout << "N";
        }
        else {
            cout << "N";
        }
    }

    return 0;
}

// 4 3
// 7 4
// LCM 1 2 2
// GCD 3 7 7
// LCM 5 6 9
// GCD 6 7 1
// 4 3 
// GCD 2 3 2
// GCD 1 3 5 
// GCD 2 4 3
// 2 2 
// LCM 1 2 10
// LCM 1 2 3