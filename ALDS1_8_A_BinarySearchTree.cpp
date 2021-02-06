// 二分探索木
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
    } else {
      inorder(root);
      cout << endl;
      preorder(root);
      cout << endl;
    }
  }
  return 0;
}
