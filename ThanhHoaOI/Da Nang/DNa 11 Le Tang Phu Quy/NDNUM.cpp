#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
//const int MOD = 2004010501;//>2e9
const int MOD = 999999937;
int lcm(int a, int b) { return a / __gcd(a, b) * b; }
void add(int& var, const int& val) { var += val; if (var >= MOD) var -= MOD; }
void subtract(int& var, const int& val) { var -= val; if (var < 0) var += MOD; }

#define task "NDNUM"
int length;

int** dp[205];
void calc_dp() {
	int base = 1;
	for (int digit = 1; digit <= 9; digit++) base = lcm(base, digit);
	int full = 1 << 9; //aka. 512

	for (int pos = 0; pos <= length; pos++) {
		dp[pos] = new int*[base];
		for (int rem = 0; rem < base; rem++) {
			dp[pos][rem] = new int[full];
			fill(dp[pos][rem], dp[pos][rem] + full, 0);		
		}
	}
	
	dp[0][0][0] = 1;
	for (int pos = 0; pos < length; pos++) for (int rem = 0; rem < base; rem++) 
		for (int msk = 0; msk < full; msk++) if (dp[pos][rem][msk]) {
			int new_rem = (10 * rem) % base;
			add(dp[pos + 1][new_rem][msk], dp[pos][rem][msk]);
			for (int digit = 1, addin = 1; digit <= 9; digit++, addin *= 2) {
				++new_rem;
				if (new_rem >= base) new_rem -= base;
				add(dp[pos + 1][new_rem][msk | addin], dp[pos][rem][msk]);
			}
		}
	
	int answer = 0;
	for (int msk = 0; msk < full; msk++) {
		int cur_base = 1;
		for (int d = 0; d < 9; d++) if ((msk >> d) & 1) cur_base = lcm(cur_base, d + 1);
		for (int rem = 0; rem < base; rem += cur_base) 
			add(answer, dp[length][rem][msk]);
	}
//	for (int pos = 0; pos <= length; pos++) delete dp[pos];
	cout << answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);

	cin >> ::length;
	
	if (length <= 6) 
	if (false)
	{
		int lim = 1;
		for (int d = 1; d <= length; d++) lim *= 10;
		int ans = 0;
		for (int i = 0; i < lim; i++) {
			bool check = true;
			for (int tmp = i; check and tmp > 0; tmp /= 10) 
				if (tmp % 10 != 0) check &= (i % (tmp % 10)) == 0;
			ans += check;
		}
		cout << ans << '\n';	
//		return cout << ans, 0;
	}

	calc_dp();
}
