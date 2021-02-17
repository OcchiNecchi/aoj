// 単一始点最短経路
// ダイクストラのアルゴリズム(ダイクストラ法)
#include <iostream>
using namespace std;

const int INF = (1 << 21);

const int N = 100;

int n;
int matrixWeight[N][N];

// 各ノードについての状態
// 訪問していないノードの状態
const int NOT_VISIT = 0;
// 訪問中のノード(未訪問の頂点を持っている可能性がある)
const int VISITING = 1;
// 訪問が完了したノード(未訪問の頂点がもうない)
const int VISITED = 2;

// プリム法と似ているため、流用している
int dijsktra() {
  // ノードの訪問状態を保持する
  int statusArray[N];
  // 親となる頂点を格納する(暫定として入っているものもある、
  // プリム法を流用しているためここに宣言されているが、今回は使わない)
  int parentVertex[N];
  // 始点から(問題では頂点0固定)、インデックスに入る頂点に到達するまでの
  // 最小の距離を保持しておく(暫定として入っているものもある)
  int minWeight[N];

  // 配列を初期化する
  for (int i = 0; i < n; i++) {
    statusArray[i] = NOT_VISIT;
    parentVertex[i] = -1;
    minWeight[i] = INF;
  }

  minWeight[0] = 0;

  int targetVertex, mincost;
  while (1) {
    mincost = INF;
    targetVertex = -1;

    // どこの頂点を調査対象とするか決める
    // 全頂点の中で、訪問完了になっていない、かつその頂点の中で到達コストが一番小さいものを
    // 今回の調査対象の頂点とする
    for (int i = 0; i < n; i++) {
      if (statusArray[i] != VISITED && minWeight[i] < mincost) {
        targetVertex = i;
        mincost = minWeight[i];
      }
    }
    // 調査対象頂点がなくなった場合
    if (targetVertex == -1) break;

    statusArray[targetVertex] = VISITED;

    // targetVertexに接する頂点を調べる
    for (int i = 0; i < n; i++) {
      // 接している頂点が調査済みではなく、targetVertexと接している頂点で(INFではない)
      // minWeightに入っている重さが、targetVertexへの最短距離とtargetVertexからiへの重さより重い場合
      // (３つ目の条件がプリム法とは違う)
      if (statusArray[i] != VISITED && matrixWeight[targetVertex][i] != INF &&
          minWeight[i] > minWeight[targetVertex] + matrixWeight[targetVertex][i]) {
        // 最小の重さ(頂点iへ到達するための最小値)を入れ替える(暫定)
        // この中で最小のものはwhileループでの次の調査対象頂点になる
        minWeight[i] = minWeight[targetVertex] + matrixWeight[targetVertex][i];

        // 頂点iの親となる頂点を格納する(暫定)
        parentVertex[i] = targetVertex;

        statusArray[i] = VISITING;
      }
    }
  }

  // 答えとなる始点(今回は0固定)から各頂点への最短距離を出力する
  for(int i = 0; i < n; i++) {
    cout << i << " " << (minWeight[i] == INF ? -1 : minWeight[i]) << endl;
  }
}

int main() {
  cin >> n;
  int weight;
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      matrixWeight[i][j] = INF;
    }
  }

  // 問題文のinput情報に合わせて変数を宣言している
  // u：頂点の番号、k：uの出次数、v：uに隣接する頂点の番号、c：重さ
  int u, k, v, c;
  for(int i = 0; i < n; i++) {
    cin >> u >> k;
    for(int j = 0; j < k; j++) {
      cin >> v >> c;
      matrixWeight[u][v] = c;
    }
  }
  dijsktra();
  return 0;
} 