#include<bits/stdc++.h>
using namespace std;

#define task "TOLLBOOTHS"

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	freopen(task".inp", "r", stdin);
	freopen(task".out", "w", stdout);

	int total, capa;
	cin >> total >> capa;
	int First = min(total, capa);
	
	int answer = 0;
	for (int x = 1; x <= First + 1; x++) {
//		cerr << "Getting to " << x << " : ";
		int remain = First - (x - 1);
		answer = max(answer, x);
//		cerr << "His family holds " << remain << '\n';
		int Second = min(total - First, capa);
//		cerr << "He can take " << Second << " when he backed\n"; 
		int get_to_family = Second - (x - 1);
		if (get_to_family < 0) continue;
//		cerr << "He has " << get_to_family << " remaining coins now\n";
		get_to_family = min(get_to_family, capa - remain);
//		cerr << "And they can use " << remain + get_to_family << '\n';
		answer = max(answer, x + remain + get_to_family);
	}	
	cout << answer;
}
