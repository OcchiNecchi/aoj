// 双方向連結リスト
#include <cstdio>
#include <cstdlib>
#include <cstring>

// 双方向連結リストのノード
struct Node {
  int key;
  Node *next, *prev;
};

// 番兵
Node *nil;

// リストを探索する
Node *listSearch(int key) {
  // 番兵の次＝リストの先頭から検索する
  Node *current = nil->next;

  // 番兵にたどり着く、もしくはkeyにたどり着くまでループする
  while (current != nil && current->key != key) {
    current = current->next;
  }
  return current;
}

// 番兵の初期化
void init() {
  nil = (Node *)malloc(sizeof(Node));
  nil->next = nil;
  nil->prev = nil;
}

// 対象ノードを削除する
void deleteNode(Node *targetNode) {
  // 番兵の場合は削除しない
  if (targetNode == nil) {
    return;
  }

  // 前後のNodeのポインタを繋ぎ変える
  targetNode->prev->next = targetNode->next;
  targetNode->next->prev = targetNode->prev;

  // メモリを開放する
  free(targetNode);
}

// リストの最初のNodeを削除する
void deleteFirst() {
  // 番兵のnextがリストの最初のNode
  deleteNode(nil->next);
}

// リストの最後のNodeを削除する
void deleteLast() {
  // 番兵のprevがリストの最後のNode
  deleteNode(nil->prev);
}

void deleteKey(int inputKey) {
  // 対象のkeyを持ったNodeを削除する
  deleteNode(listSearch(inputKey));
}

// リストに挿入、今回はリストの先頭に追加するようにする
void insert(int key) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->key = key;

  // 番兵の直後に新しいNodeを追加するため、
  // ポインタをつなぎかえる
  newNode->next = nil->next;
  nil->next->prev = newNode;
  nil->next = newNode;
  newNode->prev = nil;
}

int main() {
  int inputNum = 0;
  scanf("%d", &inputNum);

  // 番兵を初期化
  init();

  // 入力された値
  int inputKey;
  // 入力されたコマンド
  char inputCommand[20];

  for (int i = 0; i < inputNum; i++) {

    // 問題の指定でscanfの方を使用
    scanf("%s%d", inputCommand, &inputKey);

    // コマンドがinsertの場合
    if (inputCommand[0] == 'i') {
      insert(inputKey);

      // コマンドがdeleteFirstの場合
    } else if (strcmp(inputCommand, "deleteFirst") == 0) {
      deleteFirst();

      // コマンドがdeleteLastの場合
    } else if (strcmp(inputCommand, "deleteLast") == 0) {
      deleteLast();

      // コマンドがdeleteの場合
    } else {
      deleteKey(inputKey);
    }
  }

  // リストの中身を出力する
  Node *currentNode = nil->next;
  int loopCount = 0;
  while (true) {
    // 番兵までたどり着いたらループ終了
    if (currentNode == nil) {
      break;
    }

    // リストの最初以外は空白出力
    if (loopCount > 0) {
      printf(" ");
    }

    printf("%d", currentNode->key);

    currentNode = currentNode->next;
    loopCount++;
  }

  printf("\n");

  return 0;
}
