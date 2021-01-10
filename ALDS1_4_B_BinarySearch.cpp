// 2分探索
#include <iostream>
using namespace std;

// 2分探索を行う
int BinarySearch(int inputArray[], int n, int targetNum) {
  int left = 0;
  // 下記while文を< にしているため
  // rightは配列の中身＋１を指定しないと最後日の数字が探索されない
  int right = n;

  while(left < right) {
    int mid = (left + right) / 2;
    if(inputArray[mid] == targetNum) {
      return 1;
    }

    if(inputArray[mid] < targetNum) {
      left = mid + 1;
    } else {
      // midは小数以下切り捨てのため、－1すると検索対象外のアイテムが出てくるのでダメ
      right = mid;
    }
  }
  return 0;
}

int main() {
  int n = 0;
  cin >> n;

  int inputArray[100000];
  for(int i = 0; i < n; i++){
    cin >> inputArray[i];
  }

  int q = 0;
  cin >> q;
  
  // 合計が答えのため保持する
  int countSum = 0;
  int targetNum;
  for(int i = 0; i < q; i++) {
    cin >> targetNum;
    if(BinarySearch(inputArray, n, targetNum)) {
      countSum++;
    }
  }

  cout << countSum << endl;
  return 0;
}