// 連結成分
// 隣接行列ではなく、隣接リストで実装する問題
// DFSで実装する
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 100000;
const int NIL = -1;

int n;

// 隣接リストでグラフ情報を格納する(vectorをさらに配列にして宣言)
vector<int> graph[MAX];

// どのグラフのグループにいるかidを入れて割り振る配列
int statusArray[MAX];

void dfs(int targetNode, int id) {
  stack<int> dfsStack;
  dfsStack.push(targetNode);
  
  statusArray[targetNode] = id;

  while(!dfsStack.empty()) {
    int researchingNode = dfsStack.top();
    dfsStack.pop();
    for(int i = 0; i < graph[researchingNode].size(); i++) {
      int nextNode = graph[researchingNode][i];

      // もしnextNodeにグループIDが割り振られてなければ、今のidを入れる
      // また、未探索ということなので、stackにもつむ
      if(statusArray[nextNode] == NIL) {
        statusArray[nextNode] = id;
        dfsStack.push(nextNode);
      }
    }
  }
}

void checkStatus() {
  // 連結されているか調べる。同じグループに属しているか記録するようid
  int id = 1;
  for(int i = 0; i < n; i++) {
    statusArray[i] = NIL;
  }
  for(int u = 0; u < n; u++) {
    if(statusArray[u] == NIL) {
      dfs(u, id++);
    }
  }
}

int main() {
  // nはユーザー数を表す
  cin >> n;

  // mはinputされる友達関係の数を表す
  int m;
  cin >> m;

  int startNode, targetNode;
  for(int i = 0; i < m; i++) {
    cin >> startNode >> targetNode;
    graph[startNode].push_back(targetNode);
    graph[targetNode].push_back(startNode);
  }

  checkStatus();

  // 答え出力用
  int q;
  cin >> q;
  for(int i = 0; i < q; i++) {
    cin >> startNode >> targetNode;
    // statusArrayに入っているidが同じであれば、同じ部分グラフに存在している
    if (statusArray[startNode] == statusArray[targetNode]){
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
  return 0;
}