// 線形探索
#include <iostream>
using namespace std;

// 線形探索を行う
int linerSearch(int inputArray1[], int targetNum, int array1Size) {
  for(int i = 0; i < array1Size; i++) {
    if(inputArray1[i] == targetNum) {
      return 1;
    }
  }
  return 0;
}

int main() {
  int n;
  cin >> n;

  // １つ目の数列の最大数は10000
  int inputArray1[100000];
  for(int i = 0; i < n; i++) {
    cin >> inputArray1[i];
  }

  int q;
  cin >> q;

  int answerSum = 0;
  
  // 入力された値がinputArray1に存在するか確認する
  for(int i = 0; i < q; i++) {
    int inputNum = 0;
    cin >> inputNum;
    if(linerSearch(inputArray1, inputNum, n)) {
      answerSum++;
    }
  }
  cout << answerSum << endl;

  return 0;

}