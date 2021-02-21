// ダイクストラ法(優先度付きキューを用いた場合)
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n;

const int MAX = 10000;

const int INF = (1 << 21);

// 各ノードについての状態
// 訪問していないノードの状態
const int NOT_VISIT = 0;
// 訪問中のノード(未訪問の頂点を持っている可能性がある)
const int VISITING = 1;
// 訪問が完了したノード(未訪問の頂点がもうない)
const int VISITED = 2;

// 重み付き有効グラフの隣接リスト表現(pair<隣接する頂点の番号, 重さ>)
vector<pair<int, int>> matrixWeight[MAX];

// ひとつ前のダイクストラから流用している
void dijsktra() {

  // pair(当該頂点に達するまでの合計の重さ(暫定), 対象頂点)
  // vectorと逆のため注意
  priority_queue<pair<int, int>> PQ;

  // ノードの訪問状態を保持する
  int statusArray[MAX];

  // 始点から(問題では頂点0固定)、インデックスに入る頂点に到達するまでの
  // 最小の距離を保持しておく(暫定として入っているものもある)
  int minWeight[MAX];

  // 配列を初期化する
  for (int i = 0; i < n; i++) {
    statusArray[i] = NOT_VISIT;
    minWeight[i] = INF;
  }

  minWeight[0] = 0;
  PQ.push(make_pair(0, 0));
  
  while (!PQ.empty()) {
    pair<int, int> targetVertexPair = PQ.top();
    PQ.pop();
    int targetVertex = targetVertexPair.second;
    statusArray[targetVertex] = VISITED;

    // スタックに格納されている最小値がminWeightに入っているものより短くなければ次に行く
    // (なくても通ったが、あったほうが速度的に良い)
    if(minWeight[targetVertex] < targetVertexPair.first*(-1)) continue;

    // targetVertexに接する頂点を調べる
    for (int i = 0; i < matrixWeight[targetVertex].size(); i++) {
      
      int nextVertex = matrixWeight[targetVertex][i].first;

      // 接している頂点が調査済みではなく、
      // minWeightに入っている重さが、targetVertexへの最短距離とtargetVertexからiへの重さより重い場合
      if (statusArray[nextVertex] != VISITED &&
          minWeight[nextVertex] >
              minWeight[targetVertex] + matrixWeight[targetVertex][i].second) {
        // 最小の重さ(頂点iへ到達するための最小値)を入れ替える(暫定)
        // この中で最小のものはwhileループでの次の調査対象頂点になる
        minWeight[nextVertex] =
            minWeight[targetVertex] + matrixWeight[targetVertex][i].second;
        
        // priority_queueはデフォで大きい値を優先するため-1をかける
        PQ.push(make_pair(minWeight[nextVertex]*(-1), nextVertex));

        statusArray[i] = VISITING;
      }
    }
  }
  // 答えとなる始点(今回は0固定)から各頂点への最短距離を出力する
  for (int i = 0; i < n; i++) {
    cout << i << " " << (minWeight[i] == INF ? -1 : minWeight[i]) << endl;
  }
}

  int main() {
    cin >> n;

    // 問題文のinput情報に合わせて変数を宣言している
    // u：頂点の番号、k：uの出次数、v：uに隣接する頂点の番号、c：重さ
    int u, k, v, c;
    for (int i = 0; i < n; i++) {
      cin >> u >> k;
      for (int j = 0; j < k; j++) {
        cin >> v >> c;
        matrixWeight[u].push_back(make_pair(v, c));
      }
    }
    dijsktra();
    return 0;
  }