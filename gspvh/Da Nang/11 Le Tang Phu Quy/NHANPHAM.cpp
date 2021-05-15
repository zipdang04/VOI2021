#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
#define task "NHANPHAM"

const Int lim = 5e18; //> 10^18 + 10^9 * 10^5
void multiply(Int& var, const Int& positive) {
	if (var > lim / positive) var = lim + 1; else var *= positive;
}

void add(Int& var, const Int& val) {
	if (var > lim - val) var = lim + 1; else var += val;
}

Int charisma(Int day) {
	Int a[2] = {day, day + 1};
	if (a[0] % 2 == 0) a[0] /= 2;
	if (a[1] % 2 == 0) a[1] /= 2;
	Int res = a[0];
	multiply(res, a[1]);
	return res;
}

const int MAX = (int) 1e5 + 500;
int num_activities;
Int pref[MAX];

Int compute(Int day) {
	Int res = charisma(day);
	Int subtract = 0;
	if (day >= num_activities) {
		subtract = pref[num_activities];
		multiply(subtract, day / num_activities);
	}
	add(subtract, pref[day % num_activities]);
	res -= subtract;
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w",stdout);

	cin >> num_activities;
	Int req; cin >> req;
	for (int i = 1; i <= num_activities; i++) cin >> pref[i], pref[i] += pref[i - 1];
	
	Int lo = 1, hi = 3e9, ans = -1;
	while (lo <= hi) {
		Int mid = lo + hi >> 1;
//		cerr << "Compute " << mid << " = " << compute(mid) << '\n';
		if (compute(mid) < req) lo = mid + 1;
		else ans = mid, hi = mid - 1;
	}
	
	cout << ans;
}

