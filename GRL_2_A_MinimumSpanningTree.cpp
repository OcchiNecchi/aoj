// 最小全域木
// クラスカルのアルゴリズム
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 10000;
const int INF = (1<<29);

class DisjointSet {
 public:
  // 各ノードが所属する集合における高さを記録する
  vector<int> rank;

  vector<int> parentNode;

  DisjointSet(int size) {
    // 要素数を第一引数に変更し、第二引数で埋める(なくても自動で0埋め)
    rank.resize(size, 0);
    parentNode.resize(size, 0);
    for (int i = 0; i < size; i++) makeSet(i);
  }

  // 要素がxただ1つの新しい集合を作る
  void makeSet(int x) {
    rank[x] = 0;
    // 集合が自分しかいない、もしくは根の場合はparentは自分を指す
    parentNode[x] = x;
  }

  // xとyの根を用いて二つを合併する
  void unite(int x, int y) { link(findSet(x), findSet(y)); }

  // xの属する集合と、yの属する集合を合併する
  void link(int x, int y) {
    // 低いほうの木を、高いほうの木に合併させる(高さを変化させないよう)
    if (rank[x] > rank[y]) {
      parentNode[y] = x;
    } else {
      parentNode[x] = y;

      // 高さが同じの場合は、合併により高さが1増える
      if (rank[x] == rank[y]) {
        rank[y]++;
      }
    }
  }

  // xとyが同じ集合に属しているか調べる
  bool same(int x, int y) { return findSet(x) == findSet(y); }

  // xが属する集合の根を求める
  // ついでに経路圧縮を行う(parentNodeに根を設定する)
  int findSet(int x) {
    if (x != parentNode[x]) {
      parentNode[x] = findSet(parentNode[x]);
    }
    return parentNode[x];
  }
};

class Edge {
  public:
    int source, target, cost;
    Edge(int source = 0, int target = 0, int cost = 0):
    source(source), target(target), cost(cost) {}
    
    // クラスカルは、まず辺の重みで並べ替えるため、sort時に下記が必要
    bool operator < (const Edge &e) const {
      return cost < e.cost;
    }
};

// クラスカルは辺を重み順で並べ替え、それらを閉路ができないようなものだけで
// つなげると最小全域木ができるアルゴリズム
int kruskal(int N, vector<Edge> edges) {
  int totalCost = 0;

  // 重み基準で辺を並べ替える
  sort(edges.begin(), edges.end());

  DisjointSet dset = DisjointSet(N+1);

  // union-find-treeの初期化
  for(int i = 0; i < N; i++) {
    dset.makeSet(i);
  }

  int source, target;
  for(int i = 0; i < edges.size(); i++) {
    Edge edge = edges[i];

    // 頂点sourceとtargetが同じグループに所属していなければつなげる
    if(!dset.same(edge.source, edge.target)) {
      totalCost += edge.cost;
      dset.unite(edge.source, edge.target);
    }
  }
  return totalCost;
}

int main() {
  int N, M;
  cin >> N >> M;

  vector<Edge> edges;
  int source, target, cost;
  for(int i = 0; i < M; i++) {
    cin >> source >> target >> cost;
    edges.push_back(Edge(source, target, cost));
  }
  cout << kruskal(N, edges) << endl;
  return 0;
}