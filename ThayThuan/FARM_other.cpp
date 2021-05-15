#include<bits/stdc++.h>
using namespace std;

long long n, Q, P, a[10005], f[10005][10005], g[10002][10002];
long k;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k >> Q >> P;
    long cnt = Q / P;
    for (long i = 1; i <= n; i++) cin >> a[i];

    for (long i = 1; i <= n; i++)
    {
        for (long c = 1; c <= cnt; c++)
        {
            f[i][c] = max(f[i - 1][c], f[max((long)0, i - k)][c - 1] + a[i] * P);
        }
    }

    for (long i = n; i >= 1; i--)
    {
        for (long c = 1; c <= cnt; c++)
        {
            g[i][c] = max(g[i + 1][c], g[min((long)n + 1, i + k)][c - 1] + a[i] * P);
        }
    }

    long sur = Q / P;
    sur = Q - sur * P;
    long long res = f[n][cnt];
    for (long i = 1; i <= n; i++)
    {
        for (long t = 0; t <= cnt; t++)
        {
            res = max(res, a[i] * sur + f[max((long)0, i - k)][t] + g[min((long)n + 1, i + k)][cnt - t]);
        }
    }
    cout << res;
    return 0;
}
