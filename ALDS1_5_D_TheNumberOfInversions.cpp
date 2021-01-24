// 反転数
#include <iostream>
using namespace std;
typedef long long ll;

// inputの数の個数の最大数
const int MAX = 200000;

// マージ時の番兵(十分大きな値、比較時絶対にこの数より大きいのはいない)
const int SENTINEL = 2000000000;

// merge時に使用する比較用配列
int L[MAX / 2 + 2], R[MAX / 2 + 2];


// マージソートのアルゴリズムを使用する
// アルゴリズム自体はマージソートのソースから持ってきている(今回追加しているところもある)
ll merge(int inputArray[], int n, int left, int mid, int right) {
  // マージ対象の左側の個数
  int n1 = mid - left;
  // マージ対象の右側の個数
  int n2 = right - mid;

  // 今回追加分 反転数カウント
  ll cnt = 0;

  // マージ対象の左側を配列に入れる
  for (int i = 0; i < n1; i++) {
    L[i] = inputArray[left + i];
  }
  // マージ対象の右側を配列に入れる
  for (int i = 0; i < n2; i++) {
    R[i] = inputArray[mid + i];
  }

  // 比較用配列に番兵を入れておく
  L[n1] = R[n2] = SENTINEL;

  // 左、右配列それぞれの比較対象の順番
  int leftnow = 0;
  int rightnow = 0;
  for (int i = left; i < right; i++) {
    if (L[leftnow] <= R[rightnow]) {
      inputArray[i] = L[leftnow];
      leftnow++;
    } else {
      inputArray[i] = R[rightnow];
      rightnow++;
      
      // 今回追加用、反転数をカウント(左配列の数から、現在の左配列をインデックスを引けば
      // 何個反転したかがわかる)
      cnt += (n1 - leftnow);
    }
  }
  return cnt;
}

ll mergeSort(int inputArray[], int n, int left, int right) {
  // 分割時に何個反転したかを入れる変数(今回追加分)
  ll cnt1, cnt2, cnt3;
  if (left + 1 < right) {
    int mid = (left + right) / 2;

    // マージソートは分割統治法を用いるもの
    cnt1 = mergeSort(inputArray, n, left, mid);
    cnt2 = mergeSort(inputArray, n, mid, right);

    // 上記でできるところまで分割したのち、マージする
    cnt3 = merge(inputArray, n, left, mid, right);
    return cnt1 + cnt2 + cnt3;
  } else {
    return 0;
  }
}

int main() {
  int n;
  cin >> n;

  int inputArray[MAX];
  for(int i = 0; i < n; i++) { 
    cin >> inputArray[i];
  }
  ll anscnt = mergeSort(inputArray, n, 0, n);
  cout << anscnt << endl;

  return 0;
}