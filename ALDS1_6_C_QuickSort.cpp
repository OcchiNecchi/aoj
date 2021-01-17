// クイックソート
#include <iostream>
#include <string>
using namespace std;

const int MAX = 100000;

typedef struct {
  string suit;
  int value;
} Card;

// マージソート用の番兵(十分大きな値、比較時絶対にこの数より大きいのはいない)
const int SENTINEL = 2000000000;
// マージソート時に使用する比較用配列
Card L[MAX / 2 + 2], R[MAX / 2 + 2];

// ここのマージソートは当問題がクイックソートが安定しているか確認するのを
// 問うているためその確認用
void merge(Card inputArray[], int n, int left, int mid, int right) {
  // マージ対象の左側の個数
  int n1 = mid - left;
  // マージ対象の右側の個数
  int n2 = right - mid;

  // マージ対象の左側を配列に入れる
  for (int i = 0; i < n1; i++) {
    L[i] = inputArray[left + i];
  }
  // マージ対象の右側を配列に入れる
  for (int i = 0; i < n2; i++) {
    R[i] = inputArray[mid + i];
  }

  // 比較用配列に番兵を入れておく
  L[n1].value = R[n2].value = SENTINEL;

  // 左、右配列それぞれの比較対象の順番
  int leftnow = 0;
  int rightnow = 0;
  for (int i = left; i < right; i++) {
    if (L[leftnow].value <= R[rightnow].value) {
      inputArray[i] = L[leftnow];
      leftnow++;
    } else {
      inputArray[i] = R[rightnow];
      rightnow++;
    }
  }
}

// ここのマージソートは当問題がクイックソートが安定しているか確認するのを
// 問うているためその確認用
void mergeSort(Card inputArray[], int n, int left, int right) {
  if (left + 1 < right) {
    int mid = (left + right) / 2;

    // マージソートは分割統治法を用いるもの
    mergeSort(inputArray, n, left, mid);
    mergeSort(inputArray, n, mid, right);

    // 上記でできるところまで分割したのち、マージする
    merge(inputArray, n, left, mid, right);
  }
}

// パーティション、ALDS1_6_B_Partitionから今回用に改良
int partition(Card inputArray[], int n, int left, int right) {
  // パーティション時に基準となる数、今回はinput配列の最後尾になる
  int baseNum = inputArray[right].value;

  // 現在の境目となっている箇所
  int nowPartition = left;

  Card tmp;
  for (int i = left; i < right; i++) {
    // 基準値以下の場合、境目になっている大きいグループの数の一番左のものと
    // 現在調べている数を入れ替える。また境目のインデックスをインクリメントする
    if (inputArray[i].value <= baseNum) {
      tmp = inputArray[i];
      inputArray[i] = inputArray[nowPartition];
      inputArray[nowPartition] = tmp;
      nowPartition++;
    }
  }

  // 最後に最後尾にある基準値と、境目になっている大きいグループの数の一番左のものを入れ替える
  tmp = inputArray[right];
  inputArray[right] = inputArray[nowPartition];
  inputArray[nowPartition] = tmp;

  return nowPartition;
}

// クイックソート、パーティションをどんどん作っていき、境目が並び替え済みとするソート
void quickSort(Card inputArray[], int n, int left, int right) {
  if(left < right) {
    int nowPartition = partition(inputArray, n, left, right);
    quickSort(inputArray, n, left, nowPartition-1);
    quickSort(inputArray, n, nowPartition+1, right);
  }
}

int main() {
  int n;
  cin >> n;

  Card inputArrayMerge[MAX];
  Card inputArrayQuick[MAX];
  for(int i = 0; i < n; i++) {
    string inputSuit;
    cin >> inputSuit;
    inputArrayMerge[i].suit = inputSuit;
    inputArrayQuick[i].suit = inputSuit;

    int inputValue;
    cin >> inputValue;
    inputArrayMerge[i].value = inputValue;
    inputArrayQuick[i].value = inputValue;
  }

  // マージソートはクイックソートが安定かどうか確認する用
  mergeSort(inputArrayMerge, n, 0, n);
  quickSort(inputArrayQuick, n, 0, n-1);

  // クイックソートの結果がマージソートと一緒か＝安定か確認する
  int stable = 1;
  for(int i = 0; i < n; i++) {
    if(inputArrayMerge[i].suit != inputArrayQuick[i].suit) {
      stable = 0;
    }
  }

  if(stable) {
    cout << "Stable" << endl;
  } else {
    cout << "Not stable" << endl;
  }

  for (int i = 0; i < n; i++) {
    cout << inputArrayQuick[i].suit << " " << inputArrayQuick[i].value << endl;
  }

  return 0;

}