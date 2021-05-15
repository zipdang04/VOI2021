#include<bits/stdc++.h>
using namespace std;

int main() {
    freopen("REFLECTION.INP", "r", stdin);
    freopen("REFLECTION.OUT", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    long long w, h, l;
    cin >> w >> h >> l;

    long long lcm = w * l / __gcd(w, l);
    cout << lcm / w - 1 + lcm / l - 1;

    return 0;
}

