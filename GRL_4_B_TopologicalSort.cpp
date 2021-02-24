// トポロジカルソート
// 幅優先探索で実装
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

const int MAX = 100000;
const int INF = (1<<29);

// グラフの情報を格納する
vector<int> graph[MAX];

// トポロジカルソートにて整列済みとなったNodeが入る
list<int> ansList;

int N;

// ノードの訪問状態を保持する
int statusArray[MAX];
// ノードの入次数を記録する
int inDegree[MAX];

// 各ノードについての状態
// 訪問していないノードの状態
const int NOT_VISIT = 0;
// 訪問中のノード(未訪問の頂点を持っている可能性がある)
const int VISITING = 1;
// 訪問が完了したノード(未訪問の頂点がもうない)
const int VISITED = 2;

void bfs(int s) {
  queue<int> queueNode;
  queueNode.push(s);

  // 調査対象Nodeを訪問済みにする
  statusArray[s] = VISITED;

  while(!queueNode.empty()) {
    int nowNode = queueNode.front();
    queueNode.pop();
    ansList.push_back(nowNode);

    // nowNode→別Nodeを見て、訪問対象がないか調べる
    for(int i = 0; i < graph[nowNode].size(); i++) {
      int targetNode = graph[nowNode][i];
      inDegree[targetNode]--;
      
      // 入次数が0かつ未訪問の場合、次の訪問対象とする
      if (inDegree[targetNode] == 0 && statusArray[targetNode] != VISITED) {
        statusArray[targetNode] = VISITED;
        queueNode.push(targetNode);
      }
    }
  }

}

void topologicalSort() {

  // 入次数を記録する
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < graph[i].size(); j++) {
      int tmpNode = graph[i][j];
      inDegree[tmpNode]++;
    }
  }

  // 入次数が0となったものかつ、まだ訪れていないNodeを調べる
  for(int i = 0; i < N; i++) {
    if(inDegree[i] == 0 && statusArray[i] != VISITED) bfs(i);
  }

  // anslistにたまった答えを出力する
  for(list<int>::iterator it = ansList.begin(); it != ansList.end(); it++) {
    cout << *it << endl;
  }
}

int main() {
  int M;
  cin >> N >> M;

  // 配列の初期化
  for(int i = 0; i < N; i++) {
    statusArray[i] = NOT_VISIT;
    inDegree[i] = 0;
  }

  // s=辺のスタート、t=辺のターゲット
  int s, t;
  for(int i = 0; i < M; i++) {
    cin >> s >> t;
    graph[s].push_back(t);
  }

  topologicalSort();

  return 0;
}