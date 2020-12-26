// 挿入ソート
#include <algorithm>
#include <iostream>
using namespace std;
static const int MAX = 200000;

// 現在の配列の中身を出力する
void outputArray(int inputArray[], int n) { 
  for (int i = 0; i < n; i++) {

    // 出力する数字の間に空白を入れる
    if(i != n - 1){
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
  for (int i = 0; i < n; i++){
    cin >> inputArray[i];
  }

  // 並べ替え対象の値を保持しておく
  int nowValue = 0;
  
  for (int i = 0; i < n; i++) {
    nowValue = inputArray[i];

    // 既にソート済みとなっている場所を格納する(０番目は最初からソート済み)
    int sortedCursor = i - 1;

    // 配列の検査対象が0以上、かつ、現在の配列検査対象の値が、nowValueよりも大きい場合
    // 値を一つ上に置く。そうでなければそのカーソルの位置がnowvalueが入るところ
    while (sortedCursor >= 0 && nowValue < inputArray[sortedCursor]) {
      inputArray[sortedCursor + 1] = inputArray[sortedCursor];
      sortedCursor--;
    }

    // 並び替え済みの対象位置に値を入れる
    inputArray[sortedCursor + 1] = nowValue;

    // 現在の配列の中身を出力する
    outputArray(inputArray, n);
  }

  return 0;
}