#include <bits/stdc++.h>
using namespace std;

#define FOR(type, ind, a, b) for (type ind = (a); ind <= (b); ind++)
#define FORD(type, ind, a, b) for (type ind = (a); ind >= (b); ind--)

typedef long long ll;
typedef long double ld;

const int MAX = 300005;

int n, q;
char s[MAX];
set<int> op, cl;
bool isClose[MAX];

bool check(){
	int sum = 0;
	FOR(int, i, 1, n){
		sum += isClose[i] ? -1 : 1;
		if (sum < 0) return false;
	}
	return sum == 0;
}

void sub1(){
	FOR(int, _, 1, q){
		int pos; cin >> pos;
		isClose[pos] = !isClose[pos];

		FOR(int, i, 1, n){
			isClose[i] = !isClose[i];
			if (check()) break;
			isClose[i] = !isClose[i];
		}
	}
}

void sub3(){
	set<int> close;
	FOR(int, i, 1, n)
		if (isClose[i]) close.insert(i);

	FOR(int, _, 1, q){
		int pos; cin >> pos;
		isClose[pos] = true;
		close.insert(pos);

		int ans = *close.begin();
		isClose[ans] = false;
		close.erase(close.begin());
	}
}

main(){
	freopen("bracket.inp", "r", stdin);
	freopen("bracket.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> q >> s;
	FOR(int, i, 1, n)
		isClose[i] = (s[i] == ')');
	
	if (n <= 100 && q <= 100) sub1();
	else sub3();
	FOR(int, i, 1, n)
		cout << (isClose[i] ? ')' : '(');
}