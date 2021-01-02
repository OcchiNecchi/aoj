// 面積計算(標準ライブラリを使いこなそうという趣旨の問題？)
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 書籍の解説に沿った実装
int main() {
  // 入力値「＼(半角)」を格納する
  stack<int> S1;

  // その水たまりの最も左の＼の位置と、その水たまりのその時点での面積のペア
  stack<pair<int, int>> S2;

  char inputChar;

  int areaSum = 0;

  // iは場所も表す。inputがなくなるまでループ
  for(int i = 0; cin >> inputChar; i++) {
    if(inputChar == '\\') {
      // ＼の場所をスタックに詰めておく
      S1.push(i);
    } else if (inputChar == '/' && S1.size() > 0) {
      // /に対応する＼を取得する
      int leftSlash = S1.top();
      S1.pop();

      // 面積は＼の場所マイナス/の場所を加算することで取得できる
      areaSum += i - leftSlash;

      // 今回加算されたエリアの情報を保持
      int currentArea = i - leftSlash;

      // 水たまりの情報スタックに中身あり、かつ、
      // そのスタックの＼位置がleftSlashより大きい＝
      // 以前入れたスタックの水たまりが、実はもっと大きい水たまりだった場合
      while(S2.size() > 0 && S2.top().first > leftSlash) {

        // 水たまりが大きくなることが判明したため、今回の追加エリア分を加算する
        currentArea += S2.top().second;
        S2.pop();
      }

      // ＼の位置とその水たまりの面積をスタックに入れる
      S2.push(make_pair(leftSlash, currentArea));
    }
  }
  // 解答として、面積の合計を出力
  cout << areaSum << endl;

  vector<int> ans;
  // スタックの順に各水たまりの面積を出力すると
  // 解答と逆のためvectorに入れてreverseする
  while (S2.size() > 0) {
    ans.push_back(S2.top().second);
    S2.pop();
  }
  reverse(ans.begin(), ans.end());

  // 解答として水たまりの数を出力する
  cout << ans.size();

  for (int i = 0; i < ans.size(); i++) {
    cout << " ";
    // 各水たまりの面積を出力する
    cout << ans[i];
  }
  cout << endl;

  return 0;
}