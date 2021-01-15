// 最適解の計算
// トラックの最大積載量Pを求める
#include <iostream>
using namespace std;

typedef long long ll;

// 荷物の個数
int n;

// トラックの台数
int k;

// 全荷物を格納する
ll T[100000];

// 最大積載量Pのk台のトラックで何個荷物を積められるか確
int check(ll P) {
  int baggageCount = 0;
  for(int i = 0; i < k; i++) {
    
    // 現在の積載量
    ll nowLoad = 0;

    while(nowLoad + T[baggageCount] <= P) {
      nowLoad += T[baggageCount];
      baggageCount++;

      // 荷物のカウントが荷物の個数に達した場合
      if(baggageCount == n) {
        return n;
      }
    }
  }
  return baggageCount;
}

// ２分探索にて0から100000*10000(荷物の個数×１個当たりの荷物の最大重量＝Pの考えられる最大値)
// の中で最適なPを見つける。
// ２分探索に最後に行きついた値が最適なP
int solve() {
  ll left = 0;
  ll right = 100000 * 10000;
  ll mid;
  while(right - left > 1){
    mid = (left + right) / 2;

    // mid=最大積載量Pを決めて何個積めるかチェック
    int checkLoad = check(mid);

    // 全部詰めた場合はrightにmidを入れ、範囲を狭める
    if(checkLoad >= n) {
      right = mid;

    // 全部積めなかった場合はleftにmidを入れ、範囲を狭める
    }else {
      left = mid;
    }
  }
  // 最終的にrightに入っていたものが適当な最大積載量P
  return right;
}

int main() {
  // 荷物の個数＝nとトラックの台数＝kを取得する
  cin >> n >> k;

  // 荷物の情報を配列Tに格納する
  for(int i = 0; i < n; i++) {
    cin >> T[i];
  }

  ll answer = solve();
  cout << answer << endl;

  return 0;
}