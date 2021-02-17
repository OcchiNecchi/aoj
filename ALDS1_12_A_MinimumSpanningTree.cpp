// 最小全域木
// プリムのアルゴリズム(プリム法)
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

int prim() {
  // ノードの訪問状態を保持する
  int statusArray[N];
  // 親となる頂点を格納する(暫定として入っているものもある)
  int parentVertex[N];
  // 調査したことのある頂点から、インデックスに入る頂点に到達するまでの
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
      // minWeightに入っている重さがtargetVertexからiへの重さより重い場合
      if (statusArray[i] != VISITED && matrixWeight[targetVertex][i] != INF &&
          minWeight[i] > matrixWeight[targetVertex][i]) {
        
        // 最小の重さ(頂点iへ到達するための最小値)を入れ替える(暫定)
        // この中で最小のものはwhileループでの次の調査対象頂点になる
        minWeight[i] = matrixWeight[targetVertex][i];

        // 頂点iの親となる頂点を格納する(暫定)
        parentVertex[i] = targetVertex;

        statusArray[i] = VISITING;
      }
    }
  }

  // 答えとなる重みの総和を算出する
  int answerSum = 0;
  for(int i = 0; i < n; i++) {
    if(parentVertex[i] != -1) {
      answerSum += matrixWeight[i][parentVertex[i]];
    }
  }
  return answerSum;
}

int main() {
  cin >> n;

  int weight;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> weight;
      if (weight == -1) {
        matrixWeight[i][j] = INF;
      } else {
        matrixWeight[i][j] = weight;
      }
    }
  }
  cout << prim() << endl;
  return 0;
}