// ユークリッドの互除法
#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int x, int y) {
  // 常にy<xになるようにする
  if(x < y) swap(x, y);

  int tmp;
  while(true) {
    tmp = x % y;
    x = y;
    y = tmp;
    if(y == 0) break;
  }

  return x;
}

int main() {
  int a, b;
  cin >> a >> b;

  cout << gcd(a, b) << endl;

  return 0;
}