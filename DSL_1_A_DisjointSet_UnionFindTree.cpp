// 互いに素な集合
// Union Find 木
#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
  public:
    // 各ノードが所属する集合における高さを記録する
    vector<int> rank;

    vector<int> parentNode;

    DisjointSet(int size) {
      // 要素数を第一引数に変更し、第二引数で埋める(なくても自動で0埋め)
      rank.resize(size, 0);
      parentNode.resize(size, 0);
      for(int i = 0; i < size; i++) makeSet(i);
    }


    // 要素がxただ1つの新しい集合を作る
    void makeSet(int x) {
      rank[x] = 0;
      // 集合が自分しかいない、もしくは根の場合はparentは自分を指す
      parentNode[x] = x;
    }

    // xとyの根を用いて二つを合併する
    void unite(int x, int y) {
      link(findSet(x), findSet(y));
    }

    // xの属する集合と、yの属する集合を合併する
    void link(int x, int y) {
      // 低いほうの木を、高いほうの木に合併させる(高さを変化させないよう)
      if(rank[x] > rank[y]) {
        parentNode[y] = x;
      } else {
        parentNode[x] = y;
        
        // 高さが同じの場合は、合併により高さが1増える
        if(rank[x] == rank[y]) {
          rank[y]++;
        }
      }
    }

    // xとyが同じ集合に属しているか調べる
    bool same(int x, int y) {
      return findSet(x) == findSet(y);
    }

    // xが属する集合の根を求める
    // ついでに経路圧縮を行う(parentNodeに根を設定する)
    int findSet(int x) {
      if(x != parentNode[x]) {
        parentNode[x] = findSet(parentNode[x]);
      }
      return parentNode[x];
    }
};

int main() {

  int n;
  cin >> n;

  // n個の互いに素な集合を作成する
  DisjointSet ds = DisjointSet(n);

  // 命令の数が格納されている
  int q;
  cin >> q;

  int command, xNode, yNode;
  for(int i = 0; i < q; i++) {
    cin >> command >> xNode >> yNode;
  
    if(command == 0) ds.unite(xNode, yNode);
    else if(command == 1) {
      if(ds.same(xNode, yNode)) cout << 1 << endl;
      else cout << 0 << endl;
    }
  }
  return 0;
}