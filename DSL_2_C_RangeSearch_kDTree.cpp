// kD木
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX = 1000000;
const int NIL = -1;

class Node {
  public:
    int location;
    int parentNode, leftNode, rightNode;
    Node() {}
};

class Point {
  public:
    int id, x, y;
    Point() {}
    // :より右はC++のイニシャライザ。コンストラクタの処理前に初期化する
    Point(int id, int x, int y): id(id), x(x), y(y){}

    bool operator < ( const Point &p) const {
      return id < p.id;
    }

    // 答え出力時に使用
    void print() {
      printf("%d\n", id);
    }
};

int N;
Node nodeArray[MAX];
Point pointArray[MAX];
int nodePoint;

// lessXやlessYはプレディケート、sort関数使用時、Pointクラスを整列するため
// 何を基準にsortさせるかを第３引数に設定する
bool lessX(const Point &p1, const Point &p2) {
  return p1.x < p2.y;
}

bool lessY(const Point &p1, const Point &p2) {
  return p1.y < p2.y;
}

int makeKDTree(int leftNode, int rightNode, int depth) {
  if(leftNode >= rightNode) return NIL;
  int mid = (leftNode + rightNode) / 2;

  int nowNodePoint = nodePoint++;

  // 2分探索木にて、偶数がx座標、奇数がy座標
  // pointArrayのleftNodeからrightNodeまでをx基準かy基準で並べ替える
  if(depth % 2 == 0) {
    sort(pointArray + leftNode, pointArray + rightNode, lessX);
  } else {
    sort(pointArray + leftNode, pointArray + rightNode, lessY);
  }

  // location にはpointArrayでの場所が入っている
  nodeArray[nowNodePoint].location = mid;
  nodeArray[nowNodePoint].leftNode = makeKDTree(leftNode, mid, depth + 1);
  nodeArray[nowNodePoint].rightNode = makeKDTree(mid + 1, rightNode, depth+1);
  return nowNodePoint;
}

void find(int nowNode, int sx, int tx, int sy, int ty, int depth, vector<Point> &ansVector) {
  // 対象Nodeの座標を取り出す
  int x = pointArray[nodeArray[nowNode].location].x;
  int y = pointArray[nodeArray[nowNode].location].y;

  if(sx <= x && x <= tx && sy <= y && y <= ty) {
    ansVector.push_back(pointArray[nodeArray[nowNode].location]);
  }

  // 深さの偶奇によってx座標かy座標かで並べ替えられているか違うので判定を分ける
  if(depth % 2 == 0) {
    if(nodeArray[nowNode].leftNode != NIL) {
      if(sx <= x) find(nodeArray[nowNode].leftNode, sx, tx, sy, ty, depth+1, ansVector);
    }
    if (nodeArray[nowNode].rightNode != NIL) {
      if (x <= tx) find(nodeArray[nowNode].rightNode, sx, tx, sy, ty, depth + 1, ansVector);
    }
  } else {
    if (nodeArray[nowNode].leftNode != NIL) {
      if (sy <= y) find(nodeArray[nowNode].leftNode, sx, tx, sy, ty, depth + 1, ansVector);
    }
    if (nodeArray[nowNode].rightNode != NIL) {
      if (y <= ty) find(nodeArray[nowNode].rightNode, sx, tx, sy, ty, depth + 1, ansVector);
    }
  }
}

int main() {
  scanf("%d", &N);
  int x, y;
  for(int i = 0; i < N; i++) {
    scanf("%d %d", &x, &y);
    pointArray[i] = Point(i, x, y);
    nodeArray[i].leftNode = nodeArray[i].rightNode = nodeArray[i].parentNode = NIL;
  }

  nodePoint = 0;

  int rootNode = makeKDTree(0, N, 0);

  int q;
  scanf("%d", &q);
  int sx, tx, sy, ty;
  vector<Point> ansVector;
  for(int i = 0; i < q; i++) {
    scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
    ansVector.clear();
    find(rootNode, sx, tx, sy, ty, 0, ansVector);
    sort(ansVector.begin(), ansVector.end());
    for(int j = 0; j < ansVector.size(); j++) {
      ansVector[j].print();
    }
    printf("\n");
  }
  return 0;
}