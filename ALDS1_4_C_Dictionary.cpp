// ハッシュ法
#include <string.h>
#include <iostream>
#include <string>
typedef long long ll;
using namespace std;

// 素数
// ハッシュ生成時、割る数を素数でないといけないため、
// 十分大きな素数を設定(書籍コードから)
const int PRIME_NUMBER = 1046527;

// データを入れるハッシュテーブル
// マップや辞書みたいなもの
// 1,ハッシュ値、2,input文字(最大12文字まで制限あり)
char hashTable[PRIME_NUMBER][14];

// 文字から数値に変換する
// 問題の制限上、input文字はA、C、G、Tのみ
int getChar(char ch) {
  if (ch == 'A')
    return 1;
  else if (ch == 'C')
    return 2;
  else if (ch == 'G')
    return 3;
  else if (ch == 'T')
    return 4;
  else
    return 0;
}

// 文字列から数値に変換してkeyを生成する
ll getKey(char inputValue[]) {
  ll sum = 0;

  // ABCDとBCDAみたいに並びだけ違う文字列でも、数値が違うものが出るよう、都度値をかける
  ll p = 1;

  for (int i = 0; i < strlen(inputValue); i++) {
    sum += p*getChar(inputValue[i]);

    // 実験したが別に3とかでも通りはした。数字はともかく、かけることが大事
    p *= 5;
  }
  return sum;
}

int hashGenerate1(int key) { return key % PRIME_NUMBER; }

int hashGenerate2(int key) { return 1 + (key % (PRIME_NUMBER - 1)); }

// 入力値がハッシュテーブルに存在するか確認する
int find(char inputValue[]) {
  // 文字列を数字(ハッシュ)に変換する
  ll key;
  key = getKey(inputValue);

  ll hash;
  for(int i = 0;; i++) {
    // ハッシュ衝突時はiが１以上になっておりハッシュが再計算される
    hash = (hashGenerate1(key) + i * hashGenerate2(key)) % PRIME_NUMBER;
    
    if(strcmp(hashTable[hash], inputValue) == 0) {
      return 1;
    }else if(strlen(hashTable[hash]) == 0) {
      return 0;
    }
  }
  return 0;
}

// 入力値をハッシュテーブルに入れる
int insert(char inputValue[]) {
  // 文字列を数字(ハッシュ)に変換する
  ll key;
  key = getKey(inputValue);

  ll hash;
  // ダブルハッシュを用いたオープンアドレス法
  for (int i = 0;; i++) {

    // ハッシュ衝突時はiが１以上になっておりハッシュが再計算される
    hash = (hashGenerate1(key) + i * hashGenerate2(key)) % PRIME_NUMBER;

    // strcmpが0 = ハッシュテーブルに既に入力値が存在している場合
    if(strcmp(hashTable[hash], inputValue) == 0) {
      return 0;
    
    // ターゲットのハッシュテーブルに値が入っていない場合
    } else if(strlen(hashTable[hash]) == 0) {
      strcpy(hashTable[hash], inputValue);
      return 0;
    }

    //-- 対象のハッシュテーブルに値が入っているが、入力値ではない場合(ハッシュ衝突)
    // もう一度ループを回して計算する
  }
  return 0;
}

int main() {
  int n = 0;
  cin >> n;

  // ハッシュテーブルを初期化
  for(int i = 0; i < PRIME_NUMBER; i++) {
    hashTable[i][0] = '\0';
  }

  for (int i = 0; i < n; i++) {
    string command;
    cin >> command;
    char inputValue[14];
    cin >> inputValue;

    if (command[0] == 'i') {
      insert(inputValue);
    } else {
      if (find(inputValue)) {
        cout << "yes" << endl;
      } else {
        cout << "no" << endl;
      }
    }
  }
  return 0;
}