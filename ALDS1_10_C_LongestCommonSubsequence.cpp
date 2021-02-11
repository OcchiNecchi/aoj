// 最長共通部分列
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

const int N = 1000;

// 最長共通部分列を求めるアルゴリズム
int lcs(string inputX, string inputY) {
  int dp[N+1][N+1];

  int xsize = inputX.size();
  int ysize = inputY.size();

  // 最長共通部分列の長さ＝答え
  int answer = 0;

  // inputXやinputYの先頭に空白を入れる
  inputX = " " + inputX;
  inputY = " " + inputY;

  for(int i = 0; i <= xsize; i++) dp[i][0] = 0;
  for(int j = 1; j <= ysize; j++) dp[0][j] = 0;

  for(int i = 1; i <= xsize; i++) {
    for(int j = 1; j <= ysize; j++) {
      if(inputX[i] == inputY[j]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
      answer = max(answer, dp[i][j]);
    }
  }

  return answer;
}

int main() {
  int n;
  cin >> n;

  string s1, s2;
  for(int i = 0; i < n; i++) {
    cin >> s1 >> s2;
    cout << lcs(s1, s2) << endl;
  }
  return 0;
}