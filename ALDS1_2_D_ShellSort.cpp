// シェルソート
#include <iostream>
#include <vector>
using namespace std;
static const int MAX = 200000;

// どれくらいの間隔で挿入ソートを実施するかを保持する
// intervalは間隔という意味
vector<int> sortIntervalVector;

// 配列を移動した回数を保持する
long long transCount = 0;

// 現在の配列の中身を出力する
void outputArray(int inputArray[], int n) {
  for (int i = 0; i < n; i++) {
    cout << inputArray[i] << endl;
  }
}

// 挿入ソート
void insertSort(int inputArray[], int n, int interval) {
  // 並べ替え対象の値を保持しておく
  int nowValue = 0;

  for (int i = 0; i < n; i++) {
    nowValue = inputArray[i];

    // 既にソート済みとなっている場所を格納する(０番目は最初からソート済み)
    int sortedCursor = i - interval;

    // 配列の検査対象が0以上、かつ、現在の配列検査対象の値が、nowValueよりも大きい場合
    // 値を一つ上に置く。そうでなければそのカーソルの位置がnowvalueが入るところ
    while (sortedCursor >= 0 && nowValue < inputArray[sortedCursor]) {
      inputArray[sortedCursor + interval] = inputArray[sortedCursor];
      sortedCursor = sortedCursor - interval;

      // 配列を移動した回数を回答で出力するため、それをインクリメント
      transCount++;
    }
    // 並び替え済みの対象位置に値を入れる
    inputArray[sortedCursor + interval] = nowValue;
  }
}

// シェルソート、決めた間隔ごとに挿入ソートを実施する
void shellSort(int inputArray[], int n) {
  // どの間隔で挿入ソートを行うか決める
  // 一般的に3n+1が早いと言われているらしいのでその数列を作成する
  for (int i = 1;;) {
    if (i > n) break;
    sortIntervalVector.push_back(i);
    i = 3 * i + 1;
  }

  // 指定した間隔で挿入ソートを実施する
  for (int i = sortIntervalVector.size() - 1; i >= 0; i--) {
    insertSort(inputArray, n, sortIntervalVector[i]);
  }
}

int main() {
  // 最初の入力が個数のため、それを格納する
  int n;
  cin >> n;

  int inputArray[n];
  for (int i = 0; i < n; i++) {
    cin >> inputArray[i];
  }

  // シェルソートを実行する
  shellSort(inputArray, n);

  // shellSortにて作成された数列のサイズを出力する
  cout << sortIntervalVector.size() << endl;

  // shellSortにて作成された数列を出力する
  for (int i = sortIntervalVector.size() - 1; i >= 0; i--) {
    cout << sortIntervalVector[i];
    if (i != 0) {
      cout << " ";
    }
  }
  cout << endl;

  // 配列を移動した回数を出力する
  cout << transCount << endl;

  // 配列の中身を出力する
  outputArray(inputArray, n);

  return 0;
}