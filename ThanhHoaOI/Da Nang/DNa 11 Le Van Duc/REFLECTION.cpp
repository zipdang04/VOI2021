#include<bits/stdc++.h>
using namespace std;

//Variables
const int mxN = 1e5 + 5;
const int MOD = 1e9 + 7;
const long long oo = 1e18;
const int d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const int d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int TestCase , SubTask;

void Solve() {
//	cin >> SubTask;
	long long lcm , w , h , l;
	cin >> w >> h >> l;
	if (w % l == 0) cout << (w / l) - 1;
	else {
		lcm = w * l / __gcd(w , l);
		cout << lcm / l + lcm / w - 2;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("REFLECTION.INP" , "r" , stdin);
	freopen("REFLECTION.OUT" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



