// 8クイーン問題
#include <iostream>
using namespace std;

const int N = 8;

// クイーンの状態を表す
const int FREE = -1;
const int NOT_FREE = 1;

int row[N], col[N], dpos[2*N - 1], dneg[2*N - 1];

bool X[N][N];

// 配列をいろいろ初期化する
void initialize() {
  for(int i = 0; i < N; i++) {
    row[i] = FREE;
    col[i] = FREE;
  }
  for(int i = 0; i < 2*N-1; i++) {
    dpos[i] = FREE;
    dneg[i] = FREE;
  }
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      X[i][j] = false;
    }
  }
}

void printAns() {
  // 配置したクイーンと、既に配置指定のあったクイーンが一致していなければ
  // 答えは出力しない
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(X[i][j]) {
        if(row[i] != j) return;
      }
    }
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cout << ((row[i] == j) ? "Q" : ".");
    }
    cout << endl;
  }
}

void recursive(int i) {
  if(i == N) {
    printAns();
    return;
  }

  for(int j = 0; j < N; j++) {
    // (i, j)がすでに他のクイーンに襲撃されている場合は無視
    if(NOT_FREE == col[j] || NOT_FREE == dpos[i+j] || NOT_FREE == dneg[i - j + N - 1]){
      continue;
    }

    // (i, j)にクイーンを配置する
    row[i] = j;
    col[j] = dpos[i+j] = dneg[i - j + N - 1] = NOT_FREE;
    
    // 次の行を試す
    // 上手く配置できればi==Nの時に答えが出力される
    recursive(i+1);

    // (i, j)に配置されているクイーンを取り除く
    // 再帰が終わってここに来るときは(i, j)では上手く配置できなかったということなので
    row[i] = col[j] = dpos[i + j] = dneg[i - j + N - 1] = FREE;
  }
}

int main() {
  initialize();

  int k;
  cin >> k;
  int r, c;
  for(int i = 0; i < k; i++) {
    cin >> r >> c;
    X[r][c] = true;
  }
  recursive(0);
  return 0;
}