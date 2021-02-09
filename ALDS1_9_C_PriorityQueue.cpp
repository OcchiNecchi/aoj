// 優先度付きキュー
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MAX = 2000000;

int allNodeNum = 0;
int treeArray[MAX + 1];

// 左の子を計算する
int leftChild(int key) { return key * 2; }

// 右の子を計算する
int rightChild(int key) { return key * 2 + 1; }

// keyからの部分期のrootが子より小さい場合、移動させる
void maxHeapify(int key) {
  int leftKey = leftChild(key);
  int rightKey = rightChild(key);

  // 左の子、自分、右の子の値が最大のノードを選ぶ
  int largestKey;
  if (leftKey <= allNodeNum && treeArray[leftKey] > treeArray[key]) {
    largestKey = leftKey;
  } else {
    largestKey = key;
  }
  if (rightKey <= allNodeNum && treeArray[rightKey] > treeArray[largestKey]) {
    largestKey = rightKey;
  }

  if (largestKey != key) {
    swap(treeArray[key], treeArray[largestKey]);
    // largestKeyと入力keyが同じになるまで(子の方が値が小さくなるまで)再帰で呼び出す
    maxHeapify(largestKey);
  }
}

int extract() {
  // 根が最大値に常になる
  int rootNum = treeArray[1];

  // 根には一旦キューの末尾を格納する
  treeArray[1] = treeArray[allNodeNum];
  allNodeNum--;

  // treeの順番を並べ替える
  maxHeapify(1);

  return rootNum;
}

void increaseKey(int nowIndex, int key) {
  treeArray[nowIndex] = key;
  // 親ノードが今のノードより大きくなるまで入れ替える
  while (nowIndex > 1 && treeArray[nowIndex / 2] < treeArray[nowIndex]) {
    swap(treeArray[nowIndex], treeArray[nowIndex / 2]);
    nowIndex = nowIndex / 2;
  }
}

// inputノードを挿入する
void insert(int key) {
  allNodeNum++;
  increaseKey(allNodeNum, key);
}

int main() {
  int key;
  string command;

  while (1) {
    cin >> command;
    if (command == "end") break;

    if (command == "insert") {
      cin >> key;
      insert(key);
    }
    if (command == "extract") {
      cout << extract() << endl;
    }
  }
  return 0;
}