// 章２の導入部分
#include<iostream>
#include<algorithm>
using namespace std;
static const int MAX = 200000;

int main() { 
  int R[MAX], n;

  // 値を取得
  cin >> n;
  for (int i = 0; i < n; i++) cin >> R[i];

  // 最大値には十分小さい値を入れておく
  // 下記には入力値の差分の最大値を格納する
  int maxv = -2000000;

  // 下記には入力値の最小値を格納する
  int minv = R[0];

  for (int i = 1; i < n; i++) {
    maxv = max(maxv, R[i] - minv);
    minv = min(minv, R[i]);
  }

  cout << maxv << endl;

  return 0;
}