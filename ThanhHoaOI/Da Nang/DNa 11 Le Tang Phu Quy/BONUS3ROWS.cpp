#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
const Int INF = 1e18;
const int MOD = 2004010501;//>2e9
void maximize(Int& var, const Int& val) { var = max(var, val); }

#define task "BONUS3ROWS"
#define For(i, a, b) for (int i = min((a), (b)); i <= max((a), (b)); i++)
#define For_step(i, a, b, step) for (int i = (a); true; i += step)
const int MAX = (int) 1e5 + 100;

int ncols, num_queries;
Int board[3][MAX], dp[3][MAX];
int qux[MAX], quy[MAX], quu[MAX], quv[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);

	cin >> ncols >> num_queries;
	for (int r = 0; r < 3; r++) for (int i = 1; i <= ncols; i++) 
		cin >> board[r][i];
	
	bool is_sub2 = true;
	for (int i = 1; i <= num_queries; i++) {
		cin >> qux[i] >> quy[i] >> quu[i] >> quv[i];
		if (quy[i] > quv[i]) swap(qux[i], quu[i]), swap(quy[i], quv[i]);	
		--qux[i], --quu[i];
		is_sub2 &= abs(quu[i] - qux[i]) <= 1;
	}
	
	if (ncols <= (int) 1e6 / num_queries) { 
		for (int i = 1; i <= num_queries; i++) {
			For(x, quu[i], qux[i]) for (int y = quy[i]; y <= quv[i]; y++) dp[x][y] = -INF;
			dp[qux[i]][quy[i]] = board[qux[i]][quy[i]];
			
			int nxt = (qux[i] < quu[i]) ? +1 : -1;
			For_step(x, qux[i], quu[i], nxt) {
				for (int y = quy[i]; y <= quv[i]; y++) {
					if (y < quv[i])
						maximize(dp[x][y + 1], dp[x][y] + board[x][y + 1]);
					int _x = x + nxt;
					if (0 <= x and x < 3)
						maximize(dp[_x][y], dp[x][y] + board[_x][y]);
				}
				if (x == quu[i]) break;
			}
			
			cout << dp[quu[i]][quv[i]] << '\n';
		}
	} else
	if (is_sub2) 
	{
		
	}
}
