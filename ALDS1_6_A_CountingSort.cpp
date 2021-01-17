// 計数ソート(バケットソートとかいろいろ名前あり)
#include <iostream>
#include <string>
using namespace std;

// インプットの数列の個数の最大値
const int ARRAY_MAX = 2000000;
// インプットの数列の値の最大値
const int VALUE_MAX = 10000;

int main () {
  int n;
  cin >> n;

  // カウンタ配列を初期化
  int countArray[VALUE_MAX];
  for (int i = 0; i < VALUE_MAX; i++) {
    countArray[i] = 0;
  }

  int inputArray[ARRAY_MAX];
  for(int i = 0; i < n; i++) {
    // input数列を取り込む
    cin >> inputArray[i];

    // 対象の数が何個あるかカウントする
    countArray[inputArray[i]]++;
  }

  // カウント配列の中を累積和にする
  // この累積和がアウトプット配列のインデックスを表す
  for (int i = 1; i < VALUE_MAX; i++) {
    countArray[i] = countArray[i] + countArray[i - 1];
  }

  // インデックスとなったcountArrayを用いてアウトプット用配列に値を格納する
  int outputArray[ARRAY_MAX];
  for(int i = 0; i < n; i++) {
    countArray[inputArray[i]]--;
    outputArray[countArray[inputArray[i]]] = inputArray[i];
  }

  for(int i = 0; i < n; i++) {
    if(i != 0) {
      cout << " ";
    }
    cout << outputArray[i];
  }
  cout << endl;
  return 0;
}
