// 二分木
#include <iostream>
using namespace std;

const int MAX = 10000;
const int NIL = -1;

// 二分木の節点
struct Node {
  int parentNode;
  int rightNode;
  int leftNode;
};

// treeの情報を保持する
Node nodeArray[MAX];

// 深さを保持する
int depthArray[MAX];

// 高さを保持する
int heightArray[MAX];

// 深さを調べる
void setDepth(int nowNode, int nowDepth) {
  if (nowNode == NIL) return;
  depthArray[nowNode] = nowDepth;
  setDepth(nodeArray[nowNode].leftNode, nowDepth + 1);
  setDepth(nodeArray[nowNode].rightNode, nowDepth + 1);
}

// 高さを調べる
int setHeight(int nowNode) {
  int height1 = 0, height2 = 0;
  if (nodeArray[nowNode].leftNode != NIL) {
    height1 = setHeight(nodeArray[nowNode].leftNode) + 1;
  }
  if (nodeArray[nowNode].rightNode != NIL) {
    height2 = setHeight(nodeArray[nowNode].rightNode) + 1;
  }
  heightArray[nowNode] = (height1 > height2 ? height1 : height2);
  return heightArray[nowNode];
}

int getSibling(int nowNode) {
  // 親ノードが無い場合
  if (nodeArray[nowNode].parentNode == NIL) return NIL;

  if (nodeArray[nodeArray[nowNode].parentNode].leftNode != NIL &&
      nodeArray[nodeArray[nowNode].parentNode].leftNode != nowNode) {
    return nodeArray[nodeArray[nowNode].parentNode].leftNode;
  }

  if (nodeArray[nodeArray[nowNode].parentNode].rightNode != NIL &&
      nodeArray[nodeArray[nowNode].parentNode].rightNode != nowNode) {
    return nodeArray[nodeArray[nowNode].parentNode].rightNode;
  }
  return NIL;
}

void ansPrint(int nodeId) {
  cout << "node " << nodeId << ": ";
  cout << "parent = " << nodeArray[nodeId].parentNode << ", ";
  cout << "sibling = " << getSibling(nodeId) << ", ";

  // 次数を出力する
  int degree = 0;
  if (nodeArray[nodeId].rightNode != NIL) degree++;
  if (nodeArray[nodeId].leftNode != NIL) degree++;
  cout << "degree = " << degree << ", ";

  cout << "depth = " << depthArray[nodeId] << ", ";
  cout << "height = " << heightArray[nodeId] << ", ";

  // 今の節点がどの属性か(根か葉か内部節点か)
  if (nodeArray[nodeId].parentNode == NIL) {
    cout << "root";
  } else if (nodeArray[nodeId].leftNode == NIL && nodeArray[nodeId].rightNode == NIL) {
    cout << "leaf";
  } else {
    cout << "internal node";
  }

  cout << endl;
}

int main() {
  int n;
  cin >> n;

  // nodeArrayのparentをNILで初期化する
  for (int i = 0; i < n; i++) {
    nodeArray[i].parentNode = NIL;
  }

  int nodeId, leftChild, rightChild;
  for (int i = 0; i < n; i++) {
    cin >> nodeId >> leftChild >> rightChild;

    nodeArray[nodeId].leftNode = leftChild;
    nodeArray[nodeId].rightNode = rightChild;

    if (leftChild != NIL) nodeArray[leftChild].parentNode = nodeId;
    if (rightChild != NIL) nodeArray[rightChild].parentNode = nodeId;
  }

  // 根のnodeを探す
  int rootNode;
  for (int i = 0; i < n; i++) {
    if (nodeArray[i].parentNode == NIL) {
      rootNode = i;
    }
  }

  setDepth(rootNode, 0);
  setHeight(rootNode);

  // 結果を出力する
  for (int i = 0; i < n; i++) {
    ansPrint(i);
  }

  return 0;
}
