// 木の巡回
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

// 先行順巡回
void preParse(int nowNode) {
  if(nowNode == NIL) {
    return;
  }
  cout << " " << nowNode;
  preParse(nodeArray[nowNode].leftNode);
  preParse(nodeArray[nowNode].rightNode);
}

// 中間順巡回
void inParse(int nowNode) {
  if (nowNode == NIL) {
    return;
  }

  inParse(nodeArray[nowNode].leftNode);
  cout << " " << nowNode;
  inParse(nodeArray[nowNode].rightNode);
}

// 後行順巡回
void postParse(int nowNode) {
  if (nowNode == NIL) {
    return;
  }

  postParse(nodeArray[nowNode].leftNode);
  postParse(nodeArray[nowNode].rightNode);
  cout << " " << nowNode;
}

int main() {
  int n;
  cin >> n;

  // nodeArrayのparentをNILで初期化する
  for (int i = 0; i < n; i++) {
    nodeArray[i].parentNode = NIL;
  }

  // input情報をnodeArrayに入れていく
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

  cout << "Preorder" << endl;
  preParse(rootNode);
  cout << endl;
  cout << "Inorder" << endl;
  inParse(rootNode);
  cout << endl;
  cout << "Postorder" << endl;
  postParse(rootNode);
  cout << endl;
}