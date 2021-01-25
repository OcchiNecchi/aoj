// 最小コストソート
#include <algorithm>
#include <iostream>
using namespace std;

// 個数の最大値
const int MAX = 1000;

// 数列の数の最大値
const int VMAX = 10000;

// 数が何個か格納する
int n;

// 数列の中の最小値を補完する
int minimumNum;

// 入力された数列
int inputArray[MAX];

// 入力数列をソートしたものを入れる
int sortedArray[MAX];
// ソート後に配列の何番目に並んでいればいいかを格納する
int T[VMAX + 1];

int solve() {
  int ans = 0;

  // 入れ替え済みかどうかをここに入れる
  bool sortedBool[MAX];
  for (int i = 0; i < n; i++) {
    sortedArray[i] = inputArray[i];
    sortedBool[i] = false;
  }

  // arrayを並べ替え、sortedArrayやsortedBoolのどこにあるのか場所を記録するT配列を作成する
  sort(sortedArray, sortedArray+n);
  for(int i = 0; i < n; i++) {
    T[sortedArray[i]] = i;
  }
  
  // inputArrayにあるサークルを全部取得し、ansに加算する
  for(int i = 0; i < n; i++) {
    if(sortedBool[i]) continue;

    int current = i;
    
    // サークル内の要素の合計を保持する
    int sigmaW = 0;

    // サークル内での最小値を保持する
    int curcleMinimum = VMAX;
    // サークル内の要素の個数
    int partArray = 0;

    while(1) {
      sortedBool[current] = true;
      partArray++;

      // currentに現状入っている要素をsingleUnitに入れる
      int singleUnit = inputArray[current];
      curcleMinimum = min(curcleMinimum, singleUnit);

      sigmaW += singleUnit;

      // currentにはT配列を用いて、singleUnitに入った値は本来はどこの場所かを調べ
      // currentに入れる
      current = T[singleUnit];
      if (sortedBool[current]) break;
    }

    // 教本参照、どちらか値が小さいの方の数式にする
    ans += min(sigmaW + (partArray - 2) * curcleMinimum, curcleMinimum + sigmaW + (partArray + 1) * minimumNum);
  }
  return ans;
}

int main() {
  cin >> n;

  minimumNum = VMAX;
  for (int i = 0; i < n; i++) {
    cin >> inputArray[i];
    minimumNum = min(minimumNum, inputArray[i]);
  }

  int ans = solve();
  cout << ans << endl;

  return 0;
}