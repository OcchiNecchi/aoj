// 動的計画法
// 0-1ナップサック問題
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int NMAX = 100;
const int WMAX = 10000;

struct Item {
  int value;
  int weight;
};

int N, W;
Item items[NMAX+1];

int dpTable[NMAX+1][WMAX+1];

void dp() {
  // アイテムの数分だけループ
  for(int i = 1; i <= N; i++) {
    // W=対象容量までループ
    for(int j = 1; j <= W; j++) {
      dpTable[i][j] = dpTable[i-1][j];
      
      // アイテムの重さが今調べている容量より小さい場合
      if(items[i].weight > j) continue;

      if(dpTable[i-1][j] < dpTable[i - 1][j - items[i].weight] + items[i].value){
        dpTable[i][j] = dpTable[i - 1][j - items[i].weight] + items[i].value;
      }
    }
  }
}

int main() {
  cin >> N >> W;

  for(int i = 1; i <= N; i++) {
    cin >> items[i].value >> items[i].weight;
  }

  // dpTableの初期化
  for(int i = 0; i <= W; i++) {
    dpTable[0][i] = 0;
  }
  for(int i = 0; i <= N; i++) {
    dpTable[i][0] = 0;
  }

  dp();
  cout << dpTable[N][W] << endl;
  return 0;

}