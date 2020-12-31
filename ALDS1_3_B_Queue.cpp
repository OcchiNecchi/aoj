// キューの実装
//　ラウンドロビンスケジュールについてシミュレートする
#include <iostream>
using namespace std;
static const int MAX = 200000;

// プロセスを表す構造体
typedef struct {
  char name[100];
  int inputTime;
} InputProcess;

// プロセスを格納するキュー
InputProcess processQueue[MAX];

// キューの先頭位置(取り出し対象)
int head;
// キューの末尾(エンキューの位置)
int tail;

// エンキュー
void enqueue(InputProcess ip) {
  processQueue[tail] = ip;
  tail++;
}

// デキュー
InputProcess dequeue() { 
  InputProcess ip = processQueue[head];
  head++;
  return ip;
}

int main() {
  int n = 0;
  cin >> n;

  // 一回の処理時間(クオンタイム)
  int processTime;
  cin >> processTime;

  // 入力されたプロセスをキューに格納する
  for (int i = 1; i <= n; i++) {
    cin >> processQueue[i].name;
    cin >> processQueue[i].inputTime;
  }

  // キューの先頭と、末尾を更新する
  head = 1;
  tail = n + 1;

  // 処理時間の合計を格納する
  int allTime = 0;

  InputProcess tmpProcess;

  // 先頭と末尾が一致＝キューが空になるまでループ
  while (head != tail) {

    // キューの先頭のプロセスを取得する
    tmpProcess = dequeue();
    
    // クオンタイムよりキューから取得したプロセスの時間の方が長い場合
    if(tmpProcess.inputTime > processTime) {
      tmpProcess.inputTime -= processTime;
      allTime += processTime;
      enqueue(tmpProcess);
    } else {
      allTime += tmpProcess.inputTime;

      // プロセス処理が完了した場合は結果を出力
      cout << tmpProcess.name << " " << allTime << endl;
    }
  }
  return 0;
}