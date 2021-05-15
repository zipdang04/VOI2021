#include<bits/stdc++.h>
using namespace std;

typedef long long Int;
#define task "GCDLCM"

typedef long long Int;
const int MOD = 998244353;

const int MAX = (int) 1e5;
vector<Int> divs[MAX];
map<pair<int,int>, Int> gcd_of;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
//	proof_of_correctness();
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w",stdout);

	int theta; cin >> theta;
	int num_tests; cin >> num_tests;
	
	for (int n, m; num_tests --> 0; ) {
		bool check = true;
		gcd_of.clear();
		cin >> n >> m;
		for (int i = 1; i <= n; i++) divs[i].clear();
		for (int i = 1; i <= m; i++) {
			string type; cin >> type;
			if (type == "GCD") {
				int x, y; Int z;
				cin >> x >> y >> z;
				if (x > y) swap(x, y);
				if (gcd_of[make_pair(x,y)] != z and gcd_of[make_pair(x,y)] > 0) check = false;
				else {
					divs[x].push_back(z);
					divs[y].push_back(z);
					gcd_of[make_pair(x, y)] = z;
				}
			}
			else {
				
			}
		}
//		cerr << "VONG GUI XE " << check << '\n';
		if (check)
		for (int i = 1; i <= n; i++) if (divs[i].size()) {
			for (int a : divs[i]) for (int b : divs[i]) if (a != b) {
				if (a % b == 0) { check = false; goto out;}
			}
		}
		out : ;
		if (check) cout << 'Y'; else cout << 'N';
	}
}

