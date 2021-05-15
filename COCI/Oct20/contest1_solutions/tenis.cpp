#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <map>
#include <set>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)

long long meceva[3];
int igraci[3][100100];
int gubitaka[100100];
int gdje[100100][3];
int najbolja_pozicija[100100];
set< pair<int, int> > bio;
vector<int> best[8];

// samo za slucaj kad su im najbolje pozicije jednake
void mec(int a, int b, int p) {
    if (a == b || najbolja_pozicija[a] != p || najbolja_pozicija[b] != p)
        return;

    pair<int, int> par = make_pair(min(a, b), max(a, b));
    if (bio.count(par)) return;
    bio.insert(par);

    pair<int, int> p0(min(gdje[a][0], gdje[b][0]), max(gdje[a][0], gdje[b][0]));
    pair<int, int> p1(min(gdje[a][1], gdje[b][1]), max(gdje[a][1], gdje[b][1]));
    pair<int, int> p2(min(gdje[a][2], gdje[b][2]), max(gdje[a][2], gdje[b][2]));
    if (p2 < p0 && p2 < p1) {
        ++meceva[2];
        gubitaka[a] += (gdje[a][2] > gdje[b][2]);
        gubitaka[b] += (gdje[b][2] > gdje[a][2]);
    }
    else if (p1 < p0) {
        ++meceva[1];
        gubitaka[a] += (gdje[a][1] > gdje[b][1]);
        gubitaka[b] += (gdje[b][1] > gdje[a][1]);
    }
    else {
        ++meceva[0];
        gubitaka[a] += (gdje[a][0] > gdje[b][0]);
        gubitaka[b] += (gdje[b][0] > gdje[a][0]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    REP(i, 3) REP(j, n) {
        int igrac;
        cin >> igrac;
        --igrac;
        igraci[i][j] = igrac;
        gdje[igrac][i] = j;
    }
    REP(i, n) {
        najbolja_pozicija[i] = min(gdje[i][0],
                min(gdje[i][1], gdje[i][2]));
        int mask = 0;
        REP(j, 3)
            if (gdje[i][j] == najbolja_pozicija[i])
                mask |= (1 << j);
        best[mask].push_back(najbolja_pozicija[i]); 
    }
    REP(mask, 8)
        sort(best[mask].begin(), best[mask].end());

    // Slucaj 1: najbolja pozicija pobjednika je strogo veca od najbolje pozicije gubitnika.
    REP(i, n) {
        for (int mask = 1; mask < 8; ++mask) {
            int boljih = lower_bound(best[mask].begin(),
                    best[mask].end(), najbolja_pozicija[i])
                    - best[mask].begin();
            int podloga = -1;
            REP(j, 3)
                if ((mask >> j) & 1)
                    if (podloga == -1 || gdje[i][j] < gdje[i][podloga])
                        podloga = j;
            meceva[podloga] += boljih;
            gubitaka[i] += boljih;
        }
    }

    // Slucaj 2: najbolja pozicija pobjednika jednaka je najboljoj poziciji gubitnika.
    REP(i, n) {
        mec(igraci[0][i], igraci[1][i], i);
        mec(igraci[0][i], igraci[2][i], i);
        mec(igraci[1][i], igraci[2][i], i);
    }

    cout << meceva[0] << " " << meceva[1] << " " << meceva[2] << endl;
    REP(i, n)
        cout << n - 1 - gubitaka[i] << " ";
    cout << endl;
    return 0;
}
