#include <bits/stdc++.h>
using namespace std;

#define MAX 10001
#define NON 0
#define MOD 1000000007

typedef long long ll;

typedef pair<ll, ll> pii;

ll n, m, q;
ll currNum = 1;
ll ans[MAX] = {};

ll suitable(ll n, ll k){
    // cerr << n << ' ' << k << endl;
    ll curr = 1;
    k = min(k, n - k);
    for (int i = 1; i <= k; i++)
    {
        curr *= (n - i + 1), curr /= i;
        if (curr > q) return -1;
    }
    return curr;
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> q; q++;
    for (int i = 1; i <= m; i++)
    {
        // cerr << ">" << i << endl;
        for (currNum; currNum <= n; currNum++){
            // cerr << ">>>>" << currNum << ' ' << q << '\n';
            if (n - currNum < m - i) {cout << -1; return 0;}
            ll get = suitable(n - currNum, m - i); 
            // cerr << get << endl;
            if (get == -1) break;
            
            if (q == 0) break;
            q -= get;
            if (q == 0) {q += get; break;}
        }
        ans[i] = currNum, currNum++;
    }
    for (int i = 1; i <= m; i++)
    {
        cout << ans[i] << ' ';
    }
    
    
}