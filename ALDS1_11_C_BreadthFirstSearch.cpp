// 幅優先探索
#include <iostream>
#include <queue>
using namespace std;

const int N = 100;

const int INF = (1<<21);

int n;

// 隣接行列
int matrix[N][N];
// ノードの最短距離を記録する
int distanceArray[N];

void bfs(int startNode) {
  queue<int> bfsQueue;
  bfsQueue.push(startNode);

  for(int i = 0; i < n; i++) {
    distanceArray[i] = INF;
  }
  distanceArray[startNode] = 0;

  int targetNode;
  while(!bfsQueue.empty()) {
    targetNode = bfsQueue.front();
    bfsQueue.pop();

    for (int nextNode = 0; nextNode < n; nextNode++) {
      // nextNodeがtargetNodeの隣接ノードでは無い場合
      if(matrix[targetNode][nextNode] == 0) continue;

      // nextNodeが訪問済みの場合
      if (distanceArray[nextNode] != INF) continue;

      distanceArray[nextNode] = distanceArray[targetNode] + 1;

      bfsQueue.push(nextNode);
    } 
  }

  for(int i = 0; i < n; i++) {
    cout << i+1 << " " << (distanceArray[i] == INF ? -1: distanceArray[i]) << endl;
  }

}

int main() {
  cin >> n;

  // 隣接行列の初期化
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  // 隣接行列に今回のグラフの状態を入れる
  int nodeId, degreeNum;
  for (int i = 0; i < n; i++) {
    cin >> nodeId >> degreeNum;

    // inputはNodeIdは1からスタートだが、扱いやすいよう0スタートにする(0オリジン)
    nodeId--;

    int adjacentNode;
    for (int j = 0; j < degreeNum; j++) {
      cin >> adjacentNode;
      // NodeIdと同じで扱いやすいよう0オリジンとする
      adjacentNode--;
      matrix[nodeId][adjacentNode] = 1;
    }
  }
  bfs(0);

  return 0;
}