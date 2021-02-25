// 関節点
// DFS Tree
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAX = 100000;

vector<int> graph[MAX];
int N;

// ノードの訪問状態を保持する
int statusArray[MAX];

// 各ノードについての状態
// 訪問していないノードの状態
const int NOT_VISIT = 0;
// 訪問中のノード(未訪問の頂点を持っている可能性がある)
const int VISITING = 1;
// 訪問が完了したノード(未訪問の頂点がもうない)
const int VISITED = 2;

// 頂点の発見の順番を記録する
int prenum[MAX];

// DFS によって生成される木における頂点uの親を記録する
int parent[MAX];

int lowest[MAX];

int timer;

void dfs(int current, int prev) {
  prenum[current] = timer;
  lowest[current] = timer;
  timer++;

  statusArray[current] = VISITED;

  int nextNode;
  for(int i = 0; i < graph[current].size(); i++) {
    nextNode = graph[current][i];
    if(statusArray[nextNode] != VISITED) {
      parent[nextNode] = current;
      dfs(nextNode, current);

      // ノードnextの探索が終了した直後の処理
      lowest[current] = min(lowest[current], lowest[nextNode]);
    } else if (nextNode != prev) {
      // 辺current→nextNodeがBack-edge(DFS Treeで決まった辺以外のグラフの辺)の場合
      lowest[current] = min(lowest[current], prenum[nextNode]);
    }
  }
}

void art_points() {
  timer = 1;

  // lowestの計算
  dfs(0, -1);

  set<int> ap;
  int nodeId = 0;
  for(int i = 1; i < N; i++) {
    int parentNode = parent[i];
    if(parentNode == 0) nodeId++;
    else if (prenum[parentNode] <= lowest[i]) ap.insert(parentNode);
  }

  if(nodeId > 1) ap.insert(0);
  for(set<int>::iterator it = ap.begin(); it != ap.end(); it++) {
    cout << *it << endl;
  }
}

int main() {
  int edgeNum;
  cin >> N >> edgeNum;

  // 配列の初期化
  for (int i = 0; i < N; i++) {
    statusArray[i] = NOT_VISIT;
  }

  // s=辺のスタート、t=辺のターゲット
  int s, t;
  for(int i = 0; i < edgeNum; i++) {
    cin >> s >> t;
    graph[s].push_back(t);
    graph[t].push_back(s);
  }

  art_points();
  return 0;
}