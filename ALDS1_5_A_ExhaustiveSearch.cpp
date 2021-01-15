// 分割統治法・全探索
#include <iostream>
using namespace std;

int n;
// 組み合わせるための手持ちの数たち
int A[20];

// 入力値のMから選んだ要素を引いていく再帰関数
// i=何個目の手持ち数(A配列)からはじめるか
// m=組み合わせて作りたい数
int solve(int i, int m) {
  // m=0の場合は再帰でmが作成できたということ
  // trueを返す
  if(m == 0) return 1;
  if(i >= n) return 0;

  // iをプラス１して、iからその数が作成できるか分割統治法で調べる
  // 右のsolveのA[i]はA配列の数を使った場合ということ、結果がちょうど０になったら
  // mが作れるということ
  int res = solve(i + 1, m) || solve(i + 1, m - A[i]);
  return res;
}

int main() {

  // 組み合わせるための手持ちの数
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> A[i];
  }

  // 組み合わせ対象の数の個数
  int q;
  cin >> q;
  for(int i = 0; i < q; i++) {
    int m;
    cin >> m;
    if(solve(0, m)) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
  return 0;
}