// 素数判定
#include <iostream>
using namespace std;

int isPrime(int targetNum) {
  if(targetNum < 2) return 0;

  // 2は素数
  if(targetNum == 2) return 1;

  // 偶数は素数ではない
  if(targetNum % 2 == 0) return 0;

  // iがtargetNumの平方根以下の間まで調べればよい
  for(int i = 3; i*i <= targetNum; i+=2) {
    // 余りが無ければ素数ではない
    if(targetNum % i == 0) return 0;
  }
  return 1;
}

int main() {
  int n;
  cin >> n;

  int targetNum;
  int ans = 0;
  for(int i = 0; i < n; i++) {
    cin >> targetNum;
    if(isPrime(targetNum)) ans++;
  }
  cout << ans << endl;
  return 0;
}