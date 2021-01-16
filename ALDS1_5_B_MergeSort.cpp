// マージソート
#include <iostream>
#include <string>
using namespace std;

// inputの数の個数の最大数
const int MAX = 500000;

// マージ時の番兵(十分大きな値、比較時絶対にこの数より大きいのはいない)
const int SENTINEL = 2000000000;

// merge時に使用する比較用配列
int L[MAX/2+2], R[MAX/2+2];

// 答え出力時に何回比較したかカウントする
int anscnt;

void merge(int inputArray[], int n, int left, int mid, int right) {
  // マージ対象の左側の個数
  int n1 = mid - left;
  // マージ対象の右側の個数
  int n2 = right - mid;

  // マージ対象の左側を配列に入れる
  for(int i = 0; i < n1; i++) {
    L[i] = inputArray[left + i];
  }
  // マージ対象の右側を配列に入れる
  for(int i = 0; i < n2; i++) {
    R[i] = inputArray[mid + i];
  }

  // 比較用配列に番兵を入れておく
  L[n1] = R[n2] = SENTINEL;

  // 左、右配列それぞれの比較対象の順番
  int leftnow = 0;
  int rightnow = 0;
  for(int i = left; i < right; i++) {
    anscnt++;
    if(L[leftnow] <= R[rightnow]) {
      inputArray[i] = L[leftnow];
      leftnow++;
    } else {
      inputArray[i] = R[rightnow];
      rightnow++;
    }
  }
}

void mergeSort(int inputArray[], int n, int left, int right) {
  if(left+1 < right) {
    int mid = (left + right) / 2;

    // マージソートは分割統治法を用いるもの
    mergeSort(inputArray, n, left, mid);
    mergeSort(inputArray, n, mid, right);

    // 上記でできるところまで分割したのち、マージする
    merge(inputArray, n, left, mid, right);
  }
}


int main () {
  int n;
  int inputArray[MAX];
  
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> inputArray[i];
  }

  mergeSort(inputArray, n, 0, n);

  for(int i = 0; i < n; i++) {
    if(i != 0) {
      cout << " ";
    }
    cout << inputArray[i];
  }
  cout << endl;
  cout << anscnt << endl;
  return 0;
}