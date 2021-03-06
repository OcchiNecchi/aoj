// 最長増加部分列
// 動的計画法
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int n;

int inputArray[MAX];
int L[MAX];

int lis() {
  L[0] = inputArray[0];
  int length = 1;

  for(int i = 0; i < n; i++) {
    if(L[length-1] < inputArray[i]) {
      L[length] = inputArray[i];
      length++;
    } else {
      // lower_boundはkey(3つめ引数)以上の要素が初めて出現した位置を返す。
      // 下記は、配列Lのその場所にinputArray[i]を代入しようとしている
      *lower_bound(L, L + length, inputArray[i]) = inputArray[i];
    }
  }
  return length;
}

int main() {
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> inputArray[i];
  }
  cout << lis() << endl;
  return 0;
}