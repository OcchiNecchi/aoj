// 二分探索木 探索
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

// 二分探索木の節点
struct Node {
  int key;
  Node *parentNode;
  Node *rightNode;
  Node *leftNode;
};

// メモ ポインタ宣言、初期化しないと中身は0=NULLだった
// コンパイラが勝手に初期化する？
Node *root, *NIL;

void insert(int inputNum) {
  Node *targetNode = NIL;
  Node *nowNode = root;
  Node *inputNode;

  inputNode = (Node *)malloc(sizeof(Node));
  inputNode->key = inputNum;
  inputNode->leftNode = NIL;
  inputNode->rightNode = NIL;

  // どのNodeの下にinput情報を付けるか調べる
  while(nowNode != NIL) {

    targetNode = nowNode;
    // inputされた値が探索中のNodeより大きければ右のNode、小さければ左のNodeにする
    if(inputNode->key < nowNode->key) {
      nowNode = nowNode->leftNode;
    } else {
      nowNode = nowNode->rightNode;
    }
  }
  // targetNodeがinputされたNodeの親となる
  inputNode->parentNode = targetNode;

  // targetNodeがNILであれば、input情報がroot
  if(targetNode == NIL) {
    root = inputNode;
  // targetNodeがNILでなければ、input情報を親Nodeに入れる
  } else {
    if(inputNode->key < targetNode->key) {
      targetNode->leftNode = inputNode;
    }else {
      targetNode->rightNode = inputNode;
    }
  }
}

// 中間順巡回アルゴリズム
void inorder(Node *nowNode) {
  if(nowNode == NIL) return;
  inorder(nowNode->leftNode);
  cout << " " << nowNode->key;
  inorder(nowNode->rightNode);
}

// 先行順巡回アルゴリズム
void preorder(Node *nowNode) {
  if(nowNode == NIL) return;
  cout << " " << nowNode->key;
  preorder(nowNode->leftNode);
  preorder(nowNode->rightNode);
}

Node * find(Node *nowNode, int inputNum) {
  // 現在探索のNodeがNILでない、かつ、現在探索のNodeが探索ターゲットではないならループ
  while(nowNode != NIL && inputNum != nowNode->key) {
    if(inputNum < nowNode->key) {
      nowNode = nowNode->leftNode;
    } else {
      nowNode = nowNode->rightNode;
    }
  }
  return nowNode;
}

// 引数を根とする部分木の最小Nodeを求める
Node * treeMinimum(Node *sectionNode) {
  while(sectionNode->leftNode != NIL) {
    sectionNode = sectionNode->leftNode;
  }
  return sectionNode;
}

// 削除対象Nodeに子が２つあった場合、
// deleteNodeの次節点(中間順巡回にてdeleteNodeの次にくるもの)を取得する
Node * treeSuccessor(Node *targetNode) {
  // 右に子がいる場合は、右部分木で最も小さい節点がtargetNodeの次節点
  if(targetNode->rightNode != NIL) return treeMinimum(targetNode->rightNode);

  // 右に子が無い場合は、親をたどっていき最初に
  // 「左の子になっているような節点の親」が次節点になる、無い場合はNIL
  Node *tmpParentNode = targetNode->parentNode;
  while(tmpParentNode != NIL && targetNode == tmpParentNode->rightNode) {
    targetNode = tmpParentNode;
    tmpParentNode = tmpParentNode->parentNode;
  }
  return tmpParentNode;
}

void treeDelete(Node *targetNode) {
  // 削除対象のNode
  Node *deleteNode;
  // 上記の子
  Node *childNode;

  // 削除する節点を決める
  // 削除対象のNodeの子供のどちらかがNIL=子供が１つ以下の場合
  if(targetNode->leftNode == NIL || targetNode->rightNode == NIL) {
    deleteNode = targetNode;
  } else {
    deleteNode = treeSuccessor(targetNode);
  }

  // 削除対象deleteNodeの子childNodeを決める
  if(deleteNode->leftNode != NIL) {
    childNode = deleteNode->leftNode;
  } else {
    childNode = deleteNode->rightNode;
  }
  // 子ノードの親に、削除対象の親を設定する
  if(childNode != NIL) {
    childNode->parentNode = deleteNode->parentNode;
  }
  // 削除対象の親がNIL＝rootの場合は、rootに子ノードを設定
  if(deleteNode->parentNode == NIL) {
    root = childNode;
  // 削除対象に親がいる場合、そいつの子ノードに、今回の子ノードを設定する
  } else {
    if(deleteNode == deleteNode->parentNode->leftNode) {
      deleteNode->parentNode->leftNode = childNode;
    } else {
      deleteNode->parentNode->rightNode = childNode;
    }
  }

  if(deleteNode != targetNode) {
    targetNode->key = deleteNode->key;
  }
  free(deleteNode);
}

int main() {
  int n;
  cin >> n;

  string command;
  int inputNum;
  for (int i = 0; i < n; i++) {
    cin >> command;
    if (command == "insert") {
      cin >> inputNum;
      insert(inputNum);
    } else if(command == "find") {
      cin >> inputNum;
      Node *tmpNode = find(root, inputNum);
      if(tmpNode != NIL) cout << "yes" << endl;
      else cout << "no" << endl;
    } else if(command == "delete") {
      cin >> inputNum;
      treeDelete(find(root, inputNum));
    } else {
      inorder(root);
      cout << endl;
      preorder(root);
      cout << endl;
    }
  }
  return 0;
}
