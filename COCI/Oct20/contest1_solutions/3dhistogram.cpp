#include <bits/stdc++.h>
using namespace std;
#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

typedef long long int llint;

typedef pair<llint, llint> par;

#define X first
#define Y second

const int MAXN = 5e5 + 10;
const int OFF = 1 << 21;

llint ccw(par a, par b, par c) {
  return a.X * (b.Y - c.Y) + b.X * (c.Y - a.Y) + c.X * (a.Y - b.Y);
}

int n;
int A[MAXN], B[MAXN];

llint rj;

// to je onaj slucaj kad mi lijeva granica l intervla
// [l, r] odredjuje minimum na intervalu za oba niza A i B
// dakle, treba napraviti foru s 2 pointera
void prvi_slucaj(int lo, int mid, int hi) {
  int r = mid;
  int a_mini = A[mid], b_mini = B[mid];
  for(int l = mid; l >= lo; l--) {
    a_mini = min(a_mini, A[l]);
    b_mini = min(b_mini, B[l]);
    while(r < hi && A[r + 1] >= a_mini && B[r + 1] >= b_mini) r++;
    rj = max(rj, (llint) a_mini * b_mini * (r - l + 1));
  }
}

vector<par> tocke;

int off;
vector<par> hullovi[OFF];
int trenutni[OFF];

void obrisi_stari_tournament() {
  REP(i, 2 * off)
    hullovi[i].clear();
}

void rekurzivno_izradi_hullove(int cvor, int a, int b) {
  if(a == b) {
    if(a < (int) tocke.size()) 
      hullovi[cvor].push_back(tocke[a]);
    trenutni[cvor] = (int) hullovi[cvor].size() - 1;
    return;
  }
  rekurzivno_izradi_hullove(2 * cvor, a, (a + b) / 2);
  rekurzivno_izradi_hullove(2 * cvor + 1, (a + b) / 2 + 1, b);
  hullovi[cvor] = hullovi[2 * cvor];
  int poc = (a + b) / 2 + 1, kraj = min(b + 1, (int) tocke.size());
  FOR(i, poc, kraj) {
    int sz = (int) hullovi[cvor].size();
    while(sz >= 2 && ccw(hullovi[cvor][sz - 2], hullovi[cvor][sz - 1], tocke[i]) <= 0) {
      hullovi[cvor].pop_back();
      sz--;
    }
    hullovi[cvor].push_back(tocke[i]);
  }
  trenutni[cvor] = (int) hullovi[cvor].size() - 1;
}

void izgradi_tournament_hullova() {
  for(off = 1; off < (int) tocke.size(); off *= 2);
  obrisi_stari_tournament();
  rekurzivno_izradi_hullove(1, 0, off - 1);
}

//prilagodjeni dp, buduci da je query tocka uvijek oblika (t, 1)
llint dp(int t, par a) {
  return t * a.X + a.Y;
}

llint ispitaj_hull(int cvor, int t) {
  if(trenutni[cvor] == -1) return 0;
  while(trenutni[cvor] > 0 && dp(t, hullovi[cvor][trenutni[cvor] - 1]) >= dp(t, hullovi[cvor][trenutni[cvor]]))
    trenutni[cvor]--;
  return dp(t, hullovi[cvor][trenutni[cvor]]);
}

llint query(int cvor, int a, int b, int lo, int hi, int t) {
  if(a > hi || b < lo) return 0;
  if(a >= lo && b <= hi) return ispitaj_hull(cvor, t);
  llint lijevi = query(2 * cvor, a, (a + b) / 2, lo, hi, t);
  llint desni = query(2 * cvor + 1, (a + b) / 2 + 1, b, lo, hi, t);
  return max(lijevi, desni);
}

// to je kompliciraniji slucaj kad lijeva granica l 
// intervala [l, r]  odredjuje minimum za A, 
// a densa r minimum za B
void treci_slucaj(int lo, int mid, int hi) { 
  //ovdje mislim na minimume na lijevoj strani
  int a_mini = A[mid], b_mini = B[mid];
  //pocetak i kraj intervala koji pridruzujemo trenutom l
  //interval je oblika [poc, kraj]
  int poc = mid, kraj = mid;
  vector<par> intervali;
  vector<int> faktori;
  for(int l = mid; l >= lo; l--) { 
    a_mini = min(a_mini, A[l]);
    b_mini = min(b_mini, B[l]);
    while(kraj < hi && A[kraj + 1] >= a_mini) kraj++;
    while(poc <= hi && B[poc] > b_mini) poc++;
    intervali.push_back(par(poc - mid, kraj - mid));
    faktori.push_back(a_mini);
  }
  //postavljam tocke nad kojima cu graditi hullove
  tocke.clear();
  int mini_desno = B[mid];
  for(int r = mid; r <= hi; r++) {
    mini_desno = min(mini_desno, B[r]);
    tocke.push_back(par(mini_desno, (llint) mini_desno * (r + 1)));
  }
  
  izgradi_tournament_hullova();

  //upiti:
  for(int l = mid; l >= lo; l--) {
    int i = mid - l;
    rj = max(rj, (llint) faktori[i] * query(1, 0, off - 1, intervali[i].X, intervali[i].Y, -1 * l));
  }
}

void divide_and_conquer(int lo, int hi, int lijevo) {
  if(lo > hi) return;
  if(lijevo) { 
    int mid = (lo + hi) / 2; 
    prvi_slucaj(lo, mid, hi);
    treci_slucaj(lo, mid, hi);
    if(lo == hi) return;
    divide_and_conquer(lo, mid - 1, lijevo);
    divide_and_conquer(mid + 1, hi, lijevo);
  }
  else { //desno 
    int mid = (lo + hi + 1) / 2; 
    prvi_slucaj(lo, mid, hi);
    treci_slucaj(lo, mid, hi);
    if(lo == hi) return;
    divide_and_conquer(mid + 1, hi, lijevo);
    divide_and_conquer(lo, mid - 1, lijevo);
  }
}

void rijesi() {
  divide_and_conquer(0, n - 1, 1);
  reverse(A, A + n); reverse(B, B + n);
  divide_and_conquer(0, n - 1, 0);
}

int main() {
  scanf("%d", &n);
  REP(i, n) 
    scanf("%d %d", &A[i], &B[i]);
  rijesi();
  printf("%lld\n", rj);
  return 0;
}

