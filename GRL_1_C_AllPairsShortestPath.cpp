// 全点対間最短経路問題(APSP)
// ワーシャルフロイド法
#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
typedef long long ll;

// 頂点の最大個数は100
const int MAX = 100;

const ll INF = (1LL << 32);

int n;

ll dynamic[MAX][MAX];

void floyd() {
  // kは、iからjに行くまでの中間地点
  for(int k = 0; k < n; k++) {
    for(int i = 0; i < n; i++) {
      // iからkへ有向辺がなければ次へ
      if(dynamic[i][k] == INF) continue;
      
      for(int j = 0; j < n; j++) {
        // kからjへの有向辺がなければ次へ
        if(dynamic[k][j] == INF) continue;

        dynamic[i][j] = min(dynamic[i][j], dynamic[i][k] + dynamic[k][j]);  
      }
    }
  }
}


int main() {
  cin >> n;

  int edge;
  cin >> edge;

  // 2次元配列を初期化する
  // i ==jであれば0、それ以外はINFを入れる
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      dynamic[i][j] = ((i == j ? 0 : INF));
    }
  }

  // inputの重み付き有向グラフの情報を格納する
  // 変数は問題文から、s=辺のスタート、t=辺のターゲット、c=重み
  int s, t, c;
  for(int i = 0; i < edge; i++) {
    cin >> s >> t >> c;
    dynamic[s][t] = c;
  }

  floyd();

  // dynamic[i][i]がマイナス＝閉路でマイナスがある場合は NEGATIVE CYCLEと出力する
  bool negative = false;
  for(int i = 0; i < n; i++) if(dynamic[i][i] < 0) negative = true;

  if(negative) {
    cout << "NEGATIVE CYCLE" << endl;
  } else {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        if(j) cout << " ";
        if(dynamic[i][j] == INF) cout << "INF";
        else cout << dynamic[i][j];
      }
      cout << endl;
    }
  }
  return 0;
}
