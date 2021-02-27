// 木の直径
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 100000;
const int INF (1<<30);

int n;

class Edge {
  public:
    int t, w;
    Edge() {}
    Edge(int t, int w): t(t), w(w) {}
};

// グラフの情報を格納する
vector<Edge> graph[MAX];
// ノードの距離を記録する
int distanceArray[MAX];

void bfs(int s) {
  // 配列の初期化
  for (int i = 0; i < n; i++) {
    distanceArray[i] = INF;
  }
  
  queue<int> bfsQueue;
  bfsQueue.push(s);

  distanceArray[s] = 0;

  int targetNode;
  while(!bfsQueue.empty()) {
    targetNode = bfsQueue.front();
    bfsQueue.pop();

    for(int nextNode = 0; nextNode < graph[targetNode].size(); nextNode++) {
      Edge edge = graph[targetNode][nextNode];
      if(distanceArray[edge.t] == INF) {
        distanceArray[edge.t] = distanceArray[targetNode] + edge.w;
        bfsQueue.push(edge.t);
      }
    }
  }
}

void solve() {
  // 適当な節点sから最も遠い節点tgtをもとめる
  bfs(0);
  int maxv = 0;
  int tgt = 0;
  for(int i = 0; i < n; i++) {
    if(distanceArray[i] == INF) continue;
    if(maxv < distanceArray[i]) {
      maxv = distanceArray[i];
      tgt = i;
    }
  }

  // tgtから最も遠い節点の距離を求める
  bfs(tgt);
  maxv = 0;
  for (int i = 0; i < n; i++) {
    if (distanceArray[i] == INF) continue;
    maxv = max(maxv, distanceArray[i]);
  }
  cout << maxv << endl;
}

int main() {
  cin >> n;

  int s, t, w;
  for(int i = 0; i < n-1; i++) {
    cin >> s >> t >> w;
    graph[s].push_back(Edge(t, w));
    graph[t].push_back(Edge(s, w));

  }

  solve();
  return 0;
}