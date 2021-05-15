#include <bits/stdc++.h>
using namespace std;

const int LIM = 1e6;

long long a[100005];

long long calc(long long x, long long y) {
    return x * (x + 1) - 2 * x * y;
}

int main() {
    freopen("NHANPHAM.INP", "r", stdin);
    freopen("NHANPHAM.OUT", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    int n;
    long long k;
    cin >> n >> k;

    bool sub3 = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        
        if (a[i] > LIM) sub3 = 0;
    }
    
    if (n == 1 && k == 0) {
        cout << 2 * a[1] - 1;
    }
    else if (n == 1) {
        long long lower = 1, upper = 3e9;        
        while (lower < upper) {
            long long mid = (lower + upper) / 2;
            long long val = calc(mid, a[1]);
            
            if (val >= 2 * k) {
                upper = mid;
            }
            else {
                lower = mid + 1;
            }
        }
        if (calc(lower, a[1]) < 2 * k) lower = -1;
        cout << lower;
    }
    else {
        long long res = -1;
        long long sum = 0;
        for (int i = 1; i <= 1000000; i++) {
            int id = i % n;
            if (id == 0) id += n;

            sum += i - a[id];
            if (sum >= k) {
                res = i;
                break;
            }
        }
        cout << res;
    }

    return 0;
}