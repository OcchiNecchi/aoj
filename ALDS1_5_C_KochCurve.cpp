// コッホ曲線(再帰で求める)
#include <iostream>
#include <math.h>
#include <math.h>
using namespace std;

// 座標情報を保持する
struct Point {
  double x;
  double y;
};

// n=再帰の深さ、aとb=線分の端点
void koch(int n, Point a, Point b) {
  if(n == 0) {
    return;
  }

  // コッホ曲線を描く３点
  Point s, t, u;
  // 度からラジアンへ単位変換
  double th = M_PI * 60.0 / 180.0;

  // 線分a、bを三等分する点s、tを求める
  s.x = (2.0 * a.x + 1.0 * b.x) / 3.0;
  s.y = (2.0 * a.y + 1.0 * b.y) / 3.0;
  t.x = (1.0 * a.x + 2.0 * b.x) / 3.0;
  t.y = (1.0 * a.y + 2.0 * b.y) / 3.0;

  // 回転行列を用いて点u(出っ張ってる点)を求める
  u.x = (t.x - s.x) * cos(th) - (t.y - s.y) * sin(th) + s.x;
  u.y = (t.x - s.x) * sin(th) + (t.y - s.y) * cos(th) + s.y;

  koch(n-1, a, s);
  printf("%.8f %.8f\n", s.x, s.y);
  koch(n - 1, s, u);
  printf("%.8f %.8f\n", u.x, u.y);
  koch(n - 1, u, t);
  printf("%.8f %.8f\n", t.x, t.y);
  koch(n - 1, t, b);
}

int main() {
  Point a, b;

  // 何度コッホ曲線を描くか(再帰の深さがどれくらいか)inputがある
  int n;
  cin >> n;

  // 初期座標を入れる→(0,0)と(100,0)
  a.x = 0;
  a.y = 0;
  b.x = 100;
  b.y = 0;

  printf("%.8f %.8f\n", a.x, a.y);
  koch(n, a, b);
  printf("%.8f %.8f\n", b.x, b.y);

  return 0;
}