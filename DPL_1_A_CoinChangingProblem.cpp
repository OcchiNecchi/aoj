// 動的計画法
// コイン問題
#include <iostream>
#include <algorithm>
using namespace std;

const int MMAX = 20;
const int NMAX = 50000;
const int INF = (1<<29);

int main() {
  // n=円、m=コインの種類数
  int n, m;
  cin >> n >> m;

  int coin[MMAX+1];
  for(int i = 1; i <= m; i++) {
    cin >> coin[i];
  }
  int dpTable[NMAX+1];

  for(int i = 0; i <= NMAX; i++) dpTable[i] = INF;

  dpTable[0] = 0;
  for(int i = 1; i <= m; i++) {
    for(int j = 0; j + coin[i] <= n; j++) {
      dpTable[j + coin[i]] = min(dpTable[j + coin[i]], dpTable[j] + 1);
    }
  }
  cout << dpTable[n] << endl;
  return 0;
}