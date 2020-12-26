// バブルソート
#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 200000;

// 現在の配列の中身を出力する
void outputArray(int inputArray[], int n) {
  for (int i = 0; i < n; i++) {
    // 出力する数字の間に空白を入れる
    if (i != n - 1) {
      cout << inputArray[i];
      cout << " ";
    } else {
      cout << inputArray[i];
    }
  }
  cout << endl;
}

int main() {
  // 最初の入力が個数のため、それを格納する
  int n;
  cin >> n;

  // 入力の数列を配列に格納する
  int inputArray[n];
  for (int i = 0; i < n; i++) {
    cin >> inputArray[i];
  }

  // ソート済みとなった場所を格納する
  int sorted = 0;

  // 何回要素が入れ替わったかをカウントする
  int changeCount = 0;

  // ソート済みが配列すべて行われるまでループ
  while (sorted < n) {

    // 配列末尾から、ソート済みになっている箇所までループ
    for (int j = n - 1; j > sorted; j--) {

      // ひとつ前の配列を値を比べ、自分の値(インデックスj)が小さければ、値を入れ替える
      if (inputArray[j - 1] > inputArray[j]) {
        int tmp = inputArray[j - 1];
        inputArray[j - 1] = inputArray[j];
        inputArray[j] = tmp;
        changeCount++;
      }
    }
    // 配列の頭から順にソート済みとなる
    sorted++;
  }

  // 現在の配列の中身を出力する
  outputArray(inputArray, n);

  // 要素を入れ替えた回数を出力する
  cout << changeCount << endl;

  return 0;
}