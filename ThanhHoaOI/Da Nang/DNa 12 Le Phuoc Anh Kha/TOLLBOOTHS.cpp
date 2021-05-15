#include<bits/stdc++.h>
using namespace std;

int main() {
    freopen("TOLLBOOTHS.INP", "r", stdin);
    freopen("TOLLBOOTHS.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    if (n >= k * 2) {
        cout << k + k / 2 + 1;
    }
    else if (n <= k) {
        cout << n + 1;
    }
    else {
        cout << (n - k) / 2 + k + 1;
    }

    return 0;
}

