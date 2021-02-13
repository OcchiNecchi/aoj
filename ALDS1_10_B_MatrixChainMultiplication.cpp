// 連鎖行列積
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 100;

int main() {
  int n;
  cin >> n;

  // 行と列の格納する
  // 行列AとBがあった場合(Aの列数とBの行数は同じである、行列掛け算をする場合の条件)
  // 行列Aの行数と行列Bの列数を格納する
  int p[N + 1];
  for (int i = 1; i <= n; i++) {
    int rowCount, columnCount;
    cin >> rowCount >> columnCount;
    p[i - 1] = rowCount;
    p[i] = columnCount;
  }

  // inputされた行列について、左からi番目と左からj番目(i<j)の行列積の
  // 最小値を下記matrixDp[i][j]に格納する
  int matrixDp[N + 1][N + 1];

  // i=jの場合はかけあわせる対象がない、つまり0のため初期化しておく
  for (int i = 1; i <= n; i++) {
    matrixDp[i][i] = 0;
  }

  // 計算対象とする行列の数、2からスタート
  // 最初は2つの行列にて掛け算を求める(行列M1×行列M2、行列M2×行列M3...など)
  // l=3の時は行列M1×M2×M3、M2×M3×M4...など
  for (int l = 2; l <= n; l++) {
    // iは左側の行列で何番目からスタートするか
    for (int i = 1; i <= n - l + 1; i++) {
      // jは右側の行列の何番目か
      int j = i + l - 1;

      // 十分大きな数で初期化しておく9nu7
      matrixDp[i][j] = (1 << 21);

      // kはiからjの間の掛け算の区切り
      for (int k = i; k <= j - 1; k++) {
        matrixDp[i][j] =
            min(matrixDp[i][j],
                matrixDp[i][k] + matrixDp[k + 1][j] + p[i - 1] * p[k] * p[j]);
      }
    }
  }
  // matrixDp[1][n]にはinputされた全行列の最小値が入っているため出力
  cout << matrixDp[1][n] << endl;
  return 0;
}