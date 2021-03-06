// 最大正方形
// 動的計画法
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX = 1401;

int inputSquare[MAX][MAX];
int dpTable[MAX][MAX];

int h, w;

int getLargest() {
  int maxWidth = 0;

  for(int i = 1; i <= h; i++) {
    for(int j = 1; j <= w; j++) {
      // 黒タイルの場合は0を入れる
      if(inputSquare[i][j] == 1) {
        dpTable[i][j] = 0;
      } else {
        dpTable[i][j] = min(dpTable[i-1][j], min(dpTable[i][j-1], dpTable[i-1][j-1])) + 1;
      }
      maxWidth = max(maxWidth, dpTable[i][j]);
    }
  }

  // 求めるのは面積のため掛け算して返却
  return maxWidth*maxWidth;
}

int main() {
  cin >> h >> w;
  for(int i = 1; i <= h; i++) {
    for(int j = 1; j <= w; j++) {
      cin >> inputSquare[i][j];
    }
  }

  cout << getLargest() << endl;
  return 0;
}