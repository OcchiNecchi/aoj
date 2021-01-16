// パーティション
#include <iostream>
using namespace std;

const int MAX = 100000;

int n;
int inputArray[MAX];

int partition() {
  // パーティション時に基準となる数、今回はinput配列の最後尾になる
  int baseNum = inputArray[n-1];
  
  // 現在の境目となっている箇所
  int nowPartition = 0;

  int tmp;
  for(int i = 0; i < n-1; i++) {

    // 基準値以下の場合、境目になっている大きいグループの数の一番左のものと
    // 現在調べている数を入れ替える。また境目のインデックスをインクリメントする
    if(inputArray[i] <= baseNum) {
      tmp = inputArray[i];
      inputArray[i] = inputArray[nowPartition];
      inputArray[nowPartition] = tmp;
      nowPartition++;
    }
  }

  // 最後に最後尾にある基準値と、境目になっている大きいグループの数の一番左のものを入れ替える
  tmp = inputArray[n-1];
  inputArray[n-1] = inputArray[nowPartition];
  inputArray[nowPartition] = tmp;

  return nowPartition;
}

int main() {

  cin >> n;

  for(int i = 0; i < n; i++) {
    cin >> inputArray[i];
  }

  int nowPartition = partition();

  for(int i = 0; i < n; i++) {
    if(i != 0) {
      cout << " "; 
    }

    // 基準となった数はかっこを付ける
    if(i == nowPartition) {
      cout << "[" << inputArray[nowPartition] << "]";
    } else {
      cout << inputArray[i];
    }
  }
  cout << endl;
  return 0;
}