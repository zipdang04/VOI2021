#include<bits/stdc++.h>
using namespace std;

//Shortcuts
#define ll long long
#define lb long double
#define fi first
#define se second
#define debug(a) cout << "This is value of " << #a << ": " << a << "\n";
#define ft(i , a , b) for (ll i = (ll)a ; i <= (ll)b ; i++)
#define fd(i , a , b) for (ll i = (ll)a ; i >= (ll)b ; i--)
#define lt(i , a , b , c) for (ll i = (ll)a ; i <= (ll)b ; i += (ll)c)
#define ld(i , a , b , c) for (ll i = (ll)a ; i >= (ll)b ; i -= (ll)c)
#define at(a , b) for (auto a : b)

//Functions
mt19937 rando(chrono::steady_clock::now().time_since_epoch().count());
ll random(ll l , ll r) {return (rando() % (r - l + 1) + l);};
ll getbit(ll a , ll b) {return a & (1 << b);};
ll onbit(ll a , ll b) {return a | (1 << b);};
ll offbit(ll a , ll b) {return (!getbit(a , b)) ? a : a ^ (1 << b);};

//Variables
const ll mxN = 1500 + 5;
const ll mxM = 5000 + 5;
const ll oo = 1e18;
const ll MOD = 1e9 + 7;
const ll d4i[4] = {-1 , 0 , 1 , 0} , d4j[4] = {0 , 1 , 0 , -1};
const ll d8i[8] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1} , d8j[8] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

ll TestCase;
int n , m;
ll cost[mxN] , cnt[mxM] , ex[mxN];
vector<pair<ll , pair<ll , ll>>> adj[mxN];
vector<int> path[mxN];

void dijkstra(int start) {
	ft(i , 1 , n) {
		cost[i] = oo;
		path[i].clear();	
	}
	priority_queue<pair<ll , ll> , vector<pair<ll , ll>> , greater<pair<ll , ll>>> pq;
	cost[start] = 0;
	pq.push({cost[start] , start});
	pair<ll , ll> e;
	ll cp , node , child , turn;
	
	while (!pq.empty()) {
		e = pq.top();
		pq.pop();
		cp = e.fi; 
		node = e.se;
		if (cost[node] != cp) continue;
		at(it , adj[node]) {
			child = it.fi;
			cp = it.se.fi;
			turn = it.se.se;

			if (cost[child] == cost[node] + cp) {
				at(x , path[node]) {
					path[child].push_back(x);
				}
				path[child].push_back(turn);
			}
			if (cost[child] > cost[node] + cp) {
				cost[child] = cost[node] + cp;
				pq.push({cost[child] , child});
				path[child].clear();
				path[child] = path[node];
				path[child].push_back(turn);
			}
		}
	}
	if (ex[start]) ex[start]--;
}

void Solve() {
	int subtask;
	cin >> subtask;
	cin >> n >> m;
	ft(i , 1 , m) {
		int u , v , w;
		cin >> u >> v >> w;
		adj[u].push_back(make_pair(v , make_pair(w , i)));
		ex[v]++;
	}
	ft(i , 1 , n) {
		dijkstra(i);
		ft(j , 1 , n) {
			at(e , path[j]) cnt[e] += ex[i] + 1;
		}
	}
	ft(i , 1 , m) cout << cnt[i] << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	freopen("CAULUONG.inp" , "r" , stdin);
	freopen("CAULUONG.out" , "w" , stdout);
//	cin >> TestCase;
	TestCase = 1;
	while(TestCase--)
		Solve();
	return 0;
}



