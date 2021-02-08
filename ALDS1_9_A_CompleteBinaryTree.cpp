// 完全２分木
#include <iostream>
using namespace std;

const int MAX = 10000;

// 親の節点を計算する
int parent(int key) {
  return key/2;
}

// 左の子を計算する
int leftChild(int key) {
  return key * 2;
}

// 右の子を計算する
int rightChild(int key) {
  return key * 2 + 1;
}

int main() {

  int h;
  cin >> h;

  int treeArray[MAX];
  // indexは節点の番号も表すため１からスタート
  for(int i = 1; i <= h; i++) {
    cin >> treeArray[i];
  }

  for(int i = 1; i <= h; i++) {
    cout << "node " << i << ": key = " << treeArray[i] << ", ";
    if (parent(i) > 0) cout << "parent key = " << treeArray[parent(i)] << ", ";
    if (leftChild(i) <= h) cout << "left key = " << treeArray[leftChild(i)] << ", ";
    if (rightChild(i) <= h) cout << "right key = " << treeArray[rightChild(i)] << ", ";
    cout << endl;
  }
  return 0;
}