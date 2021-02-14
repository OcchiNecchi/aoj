// グラフ
#include <iostream>
using namespace std;

const int MAX = 100;

int main() {
  int n;
  cin >> n;

  int matrix[MAX][MAX];
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  int nodeId, degreeNum;
  for(int i = 0; i < n; i++) {
    cin >> nodeId >> degreeNum;

    // inputはNodeIdは1からスタートだが、扱いやすいよう0スタートにする(0オリジン)
    nodeId--;

    int adjacentNode;
    for(int j = 0; j < degreeNum; j++) {
      cin >> adjacentNode;
      // NodeIdと同じで扱いやすいよう0オリジンとする
      adjacentNode--;
      matrix[nodeId][adjacentNode] = 1;
    }
  }

  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(j) cout << " ";
      cout << matrix[i][j];
    }
    cout << endl;
  }

  return 0;
}