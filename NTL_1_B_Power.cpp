// べき乗
// 繰り返し自乗法
#include <iostream>
#include <cmath>

using namespace std;
// unsigned = 符号なし(正数)のみとする
typedef unsigned long long ll;

const ll DEVIDE_NUM = 1000000007;

// 繰り返し自乗法、掛け算では乗算するごとに(%割る数)を行う
ll power(ll x, ll y) {
  ll res = 1;
  // 0乗であれば1を返却する
  if (y == 0) return res;

  if(y > 0) {
    res = power(x, y / 2);

    if (y % 2 == 0) res = (res * res) % DEVIDE_NUM;
    else res = (((res * res) % DEVIDE_NUM) * x) % DEVIDE_NUM;
  }
  return res;
}

int main() {
  int m, n;
  cin >> m >> n;
  cout << power(m, n) << endl;
  return 0;
}