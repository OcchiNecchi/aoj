// 最大長方形
// 動的計画法
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 1400;

int h, w;

int inputTable[MAX][MAX];
int T[MAX][MAX];

struct Rectangle {
  int height;
  int pos;
};

int getLargestRectangle(int size, int buffer[]) {
  stack<Rectangle> S;
  int maxv = 0;
  buffer[size] = 0;

  for(int i = 0; i <= size; i++) {
    Rectangle rect;
    rect.height = buffer[i];
    rect.pos = i;

    if(S.empty()) {
      S.push(rect);
    } else {
      // 今調べているrectのheightの方が高い場合はスタックに入れる
      if(S.top().height < rect.height) {
        S.push(rect);

      // 今調べているrectのheightの方が低い場合
      } else if(S.top().height > rect.height) {
        int target = i;
        while(!S.empty() && S.top().height >= rect.height) {
          Rectangle pre = S.top(); S.pop();
          int area = pre.height * (i - pre.pos);
          maxv = max(maxv, area);
          target = pre.pos;
        }
        rect.pos = target;
        S.push(rect);
      }
    }
  }
  return maxv;
}

int getLargestRectangle() {
  // 上に向かってきれいなタイルが連続する長さを調べて格納する
  for(int j = 0; j < w; j++) {
    for(int i = 0; i < h; i++) {
      
      // タイルが黒の場合
      if(inputTable[i][j]) {
        T[i][j] = 0;
      
      // タイルが白の場合
      } else {
        T[i][j] = (i > 0) ? T[i-1][j] + 1 : 1;
      }
    }
  }

  int maxv = 0;
  for(int i = 0; i < h; i++) {
    maxv = max(maxv, getLargestRectangle(w, T[i]));
  }
  return maxv;
}

int main() {
  cin >> h >> w;
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      cin >> inputTable[i][j];
    }
  }
  cout << getLargestRectangle() << endl;
  return 0;
}