#include <bits/stdc++.h>
using namespace std;

#define FOR(type, ind, a, b) for (type ind = (a); ind <= (b); ind++)
#define FORD(type, ind, a, b) for (type ind = (a); ind >= (b); ind--)

typedef long long ll;
typedef long double ld;

const int MAX = 100005;
const ld eps = 1e-9;

struct Pool{
	ll b, h, w, d;
	Pool(){b = h = w = d = 0;}
	Pool(ll b, ll h, ll w, ll d){
		this -> b = b;
		this -> h = h;
		this -> w = w;
		this -> d = d;
	}
};

ll n, V;
Pool pool[MAX];

bool cal(ld b){
	ld volume = 0;
	FOR(int, i, 1, n){
		Pool curr = pool[i];
		if (curr.b - b >= eps) continue;
		ld height = min(b - curr.b, ld(curr.h));
		volume += height * curr.w * curr.d;
	}
	return V - volume >= eps;
}

main(){
	freopen("fill.inp", "r", stdin);
	freopen("fill.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> V;
	ll minB = INT32_MAX;
	FOR(int, i, 1, n){
		ll b, h, w, d; cin >> b >> h >> w >> d;
		pool[i] = Pool(b, h, w, d);

		minB = min(minB, b);
	}	
	ll maxB = 0;
	FOR(int, i, 1, n){
		pool[i].b -= minB;
		maxB = max(maxB, pool[i].b + pool[i].h);
	}


	ld l = 0, r = maxB, ans = 0;
	while (r - l >= eps){
		ld mid = (l + r) / 2.0;
		if (cal(mid)) ans = mid, l = mid;
		else r = mid;
	}
	cout << fixed << setprecision(2) << (ans + minB);
}