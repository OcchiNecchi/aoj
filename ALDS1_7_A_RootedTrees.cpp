#include <iostream>
using namespace std;

const int MAX = 100005;

const int NIL = -1;

// 左子右兄弟表現を用いる
struct Node {
  int parentNode;
  int leftChildNode;
  int rightSiblingNode;
};

// tree情報を保持する
Node nodeArray[MAX];

// 深さを保持する
int depthArray[MAX];

// node情報を出力する
void ansPrint(int nodeId) {
  cout << "node " << nodeId << ": ";
  cout << "parent = " << nodeArray[nodeId].parentNode << ", ";
  cout << "depth = " << depthArray[nodeId] << ", ";

  // 今の節点がどの属性か(根か葉か内部節点か)
  if (nodeArray[nodeId].parentNode == NIL) {
    cout << "root, ";
  } else if (nodeArray[nodeId].leftChildNode == NIL) {
    cout << "leaf, ";
  } else {
    cout << "internal node, ";
  }

  cout << "[";

  // 子のnodeを出力する
  int nowChildNode = nodeArray[nodeId].leftChildNode;
  while(1) {
    if (nowChildNode == NIL) break;

    if (nowChildNode != nodeArray[nodeId].leftChildNode) cout << ", ";
    cout << nowChildNode;
    nowChildNode = nodeArray[nowChildNode].rightSiblingNode;
  }
  cout << "]" << endl;
}

// 再帰的に深さを求める
int recCountDepth(int nowNode, int nowDepth) {
  depthArray[nowNode] = nowDepth;
  
  // 右兄弟がいる場合は同じ深さで探索
  if(nodeArray[nowNode].rightSiblingNode != NIL) {
    recCountDepth(nodeArray[nowNode].rightSiblingNode, nowDepth);
  }
  // 左子がいる場合は深さを＋1して探索
  if(nodeArray[nowNode].leftChildNode != NIL) {
    recCountDepth(nodeArray[nowNode].leftChildNode, nowDepth + 1);
  }
}

int main () {
  int n;
  cin >> n;

  // 節点を入れる配列を初期化する
  for(int i = 0; i < n; i++) {
    nodeArray[i].parentNode = NIL;
    nodeArray[i].leftChildNode = NIL;
    nodeArray[i].rightSiblingNode = NIL;
  }

  // inputにて節点ID、子の数、子の節点IDが入ってくるためそれを入れる変数
  int nodeId, nodeNum, childNode;
  // rightSiblingを入れる際に使用する
  int nowLeftNode;
  
  for(int i = 0; i < n; i++) {
    cin >> nodeId >> nodeNum;
    for(int j = 0; j < nodeNum; j++) {
      cin >> childNode;
      
      // 最初のchildNode=一番左の子はleftChildNodeに持っておく
      if(j == 0) {
        nodeArray[nodeId].leftChildNode = childNode;
      } else {
      // nodeIdの子階層のrightに次に並んでくるNodeの情報を入れる
        nodeArray[nowLeftNode].rightSiblingNode = childNode;
      }
      // 次のinputをrightSiblingに入れるため、左側の情報を持っておく
      nowLeftNode = childNode;

      // 子の節点に親のNode情報を入れる
      nodeArray[childNode].parentNode = nodeId;
    }
  }

  // 根のnodeを探す
  int rootNode;
  for(int i = 0; i < n; i++) {
    if(nodeArray[i].parentNode == NIL) {
      rootNode = i;
    }
  }

  // 深さ情報を取得する
  recCountDepth(rootNode, 0);

  // 結果を出力する
  for(int i = 0; i < n; i++) {
    ansPrint(i);
  }

  return 0;
}