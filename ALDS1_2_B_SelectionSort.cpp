// 選択ソート
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

  int inputArray[n];
  for (int i = 0; i < n; i++) {
    cin >> inputArray[i];
  }

  // 入れ替えた回数を保持
  int changeCount = 0;

  // 配列数分ループする。
  // iはソート済みの場所を表すのも兼ねている
  for (int i = 0; i < n; i++) {

    // 最小値のインデックスを保持
    int minIndex = i;

    // ソート済み(i)からnまで調べる
    for (int j = i; j < n; j++) {
      // 今までの最小値が見つかれば配列のインデックスを保持
      if (inputArray[j] < inputArray[minIndex]) {
        minIndex = j;
      }
    }

    // 最小値のインデックスが未ソート先頭と違う場合は値を入れ替える
    if(minIndex != i){
      int tmp = inputArray[i];
      inputArray[i] = inputArray[minIndex];
      inputArray[minIndex] = tmp;

      changeCount++;
    }
  }

  outputArray(inputArray, n);

  cout << changeCount << endl;
  return 0;
}