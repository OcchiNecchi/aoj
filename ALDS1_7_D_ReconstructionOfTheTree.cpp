// 木の復元
// ローカルでは実施できなかったがAOJでは通った
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 10000;
const int NIL = -1;

// 先行順巡回の情報を保持する
vector<int> preOrderVector;

// 中間順巡回の情報を保持する
vector<int> inOrderVector;

// 後行順巡回の情報を入れる(answerとして出力する)
vector<int> postOrderVector;

int preOrderIndex = 0;

int n;

// 木を復元する
void reconstruction(int left, int right) {
  if (left >= right) return;
  int rootNode = preOrderVector[preOrderIndex];
  preOrderIndex++;

  //　中間順巡回の中でrootNodeを見つけ、それをmidの位置とする
  int mid = distance(inOrderVector.begin(),
                     find(inOrderVector.begin(), inOrderVector.end(), rootNode));
  reconstruction(left, mid);
  reconstruction(mid+1, right);

  postOrderVector.push_back(rootNode);
}

void solve() { 
  reconstruction(0, preOrderVector.size());

  for(int i = 0; i < n; i++) {
    if(i) cout << " ";
    cout << postOrderVector[i];
  }

  cout << endl;
}

int main() {
  cin >> n;

  int tmp;
  for (int i = 0; i < n; i++) {
    cin >> tmp;
    preOrderVector.push_back(tmp);
  }
  for (int i = 0; i < n; i++) {
    cin >> tmp;
    inOrderVector.push_back(tmp);
  }

  solve();

  return 0;
}