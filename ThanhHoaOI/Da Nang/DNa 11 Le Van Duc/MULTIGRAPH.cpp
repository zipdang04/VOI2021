#include<bits/stdc++.h>
using namespace std;

//Variables
const int mxN = 1e6 + 5;
const int mxID = 4e6;
const int MOD = 1e9 + 7;
const long long oo = 1e18;
const int d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const int d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int TestCase , SubTask;
long long st[mxN * 4] , cnt[mxN] , a[mxN];

void update(int id , int l , int r , int pos , int val) {
	if (l == r) {
		cnt[pos] += val;
		if (cnt[pos]) st[id] = pos;
		else st[id] = oo;
		return;
	}	
	int mid = (l + r) / 2;
	if (pos <= mid) update(id * 2 , l , mid , pos , val);
	else update(id * 2 + 1 , mid + 1 , r , pos , val);
	st[id] = min(st[id * 2] , st[id * 2 + 1]);
}

long long get(int id , int l , int r , int u , int v) {
	if (l > v || r < u) return oo;
	if (u <= l && r <= v) return st[id];
	int mid = (l + r) / 2;
	return min(get(id * 2 , l , mid , u , v) , get(id * 2 + 1 , mid + 1 , r , u , v));
}

void Solve() {
//	cin >> SubTask;
	long long n , q , x , lim = 0;
	cin >> n >> q;
	for (int i = 0; i <= mxID; i++) st[i] = oo;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		lim = max(lim , a[i]);
		update(1 , 0 , lim , a[i] , 1);
	}
	for (int e = 1; e <= q; e++) {
		int type , u , v;
		cin >> type >> u >> v;
		if (type == 1) {
			update(1 , 0 , lim , a[u] , -1);
			update(1 , 0 , lim , v , 1);
			a[u] = v;
		}
		else {
			if (u == v) {
				cout << 0 << "\n";
				continue;
			}
			x = get(1 , 0 , lim , 0 , a[u] - 1);
			if (x == oo) {
				cout << a[u] * a[v] << "\n";
				continue;
			}
			cout << min(a[u] * a[v] , x * (a[u] + a[v])) << "\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("MULTIGRAPH.INP" , "r" , stdin);
	freopen("MULTIGRAPH.OUT" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



