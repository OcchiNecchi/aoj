// 最大ヒープ
#include <iostream>
using namespace std;

const int MAX = 2000000;

int h;

int inputArray[MAX];

// 親の節点を計算する
int parent(int key) { return key / 2; }

// 左の子を計算する
int leftChild(int key) { return key * 2; }

// 右の子を計算する
int rightChild(int key) { return key * 2 + 1; }

void maxHeapify(int key) {
  int leftKey = leftChild(key);
  int rightKey = rightChild(key);
  
  // 左の子、自分、右の子の値が最大のノードを選ぶ
  int largestKey;
  if (leftKey <= h && inputArray[leftKey] > inputArray[key]) {
    largestKey = leftKey;
  } else {
    largestKey = key;
  }
  if(rightKey <= h && inputArray[rightKey] > inputArray[largestKey]) {
    largestKey = rightKey;
  }

  if(largestKey != key) {
    swap(inputArray[key], inputArray[largestKey]);
    // largestKeyと入力keyが同じになるまで(子の方が値が小さくなるまで)再帰で呼び出す
    maxHeapify(largestKey);
  }
}

int main() {
  cin >> h;
  for (int i = 1; i <= h; i++) {
    cin >> inputArray[i];
  }
  for(int i = h/2; i >= 1; i--) {
    maxHeapify(i);
  }

  for(int i = 1; i <= h; i++) {
    cout << " " << inputArray[i];
  }
  cout << endl;
  return 0;
}