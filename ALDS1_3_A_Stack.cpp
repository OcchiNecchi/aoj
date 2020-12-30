// スタック
// いろいろな実装方法があるが、書籍に基づき配列を使うこととする
#include <iostream>
#include <string>
using namespace std;

// スタックとして入力値などを入れるもの
int inputStack[10000];

// スタックポイント(スタックの頂点を指す)
int top = 0;

// スタックのプッシュ
// スタックポイントも更新し、スタックに値を入れる
void push(int inputChar) {
  top++;
  inputStack[top] = inputChar;
}

// スタックのポップ
// スタックの値を取り出し、スタックポイントを更新する
int pop() {
  int popValue = inputStack[top];
  top--;
  return popValue;
}

int main() {
  // 入力全て分ループする
  string inputChar;
  while (cin >> inputChar) {

    // 逆ポーランド記法
    // 演算子の時は計算してスタックに入れる
    // オペランド(数字)の時はそのままスタックに入れる
    if(inputChar == "+") {
      int tmpNum1 = pop();
      int tmpNum2 = pop();
      push(tmpNum1 + tmpNum2);
    } else if (inputChar == "-") {
      int tmpNum2 = pop();
      int tmpNum1 = pop();
      push(tmpNum1 - tmpNum2);
    } else if (inputChar == "*") {
      int tmpNum1 = pop();
      int tmpNum2 = pop();
      push(tmpNum1 * tmpNum2);
    } else {
      push(stoi(inputChar));
    }
  }

  // 計算結果がスタックに残っているので出力
  cout << pop() << endl;

  return 0;
}