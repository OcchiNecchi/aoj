// 深さ優先探索
// スタックで実装すると、スタック部分をキューにしてあげると幅優先になるくらい
// 同じらしいのでスタックで実装する
#include <iostream>
#include <stack>
using namespace std;

const int N = 100;

// 各ノードについての状態
// 訪問していないノードの状態
const int NOT_VISIT = 0;
// 訪問中のノード(未訪問の頂点を持っている可能性がある)
const int VISITING = 1;
// 訪問が完了したノード(未訪問の頂点がもうない)
const int VISITED = 2;

int n;

// 現在の時間を保管する
int nowTime;

// 隣接行列
int matrix[N][N];
// ノードの訪問状態を保持する
int statusArray[N];

// 今回の答え出力用、ノードの発見時間を記録する
int d[N];
// 今回の答え出力用、ノードの訪問完了時間を記録する
int f[N];

// 隣接ノードを調べる際に、どこまで調べたか、各ノードの記録をする
int nodeCountArray[N];

// 引数のNodeに隣接するNodeを番号順に取得
int next(int targetNode) {
  for(int nextNode = nodeCountArray[targetNode]; nextNode < n; nextNode++) {
    
    // targetNodeにてどこまで隣接ノードを調べたか記録する
    nodeCountArray[targetNode] = nextNode + 1;

    // 隣接ノードを持っていればそれを返却する
    if(matrix[targetNode][nextNode]) return nextNode;
  }
  // 隣接ノードが無い、もしくは全部調べている場合
  return -1;
}

// スタックを用いた深さ優先探索
void dfsVisit(int targetNode) {
  stack<int> dfsStack;
  dfsStack.push(targetNode);

  statusArray[targetNode] = VISITING;

  nowTime++;
  d[targetNode] = nowTime;

  while(!dfsStack.empty()) {
    int researchingNode = dfsStack.top();
    int researchingNextNode = next(researchingNode);

    if(researchingNextNode != -1) {
      // 隣接ノードが未訪問の場合は、訪問済みにする
      if (statusArray[researchingNextNode] == NOT_VISIT){
        statusArray[researchingNextNode] = VISITING;
        nowTime++;
        d[researchingNextNode] = nowTime;
        dfsStack.push(researchingNextNode);
      } 
    // 未探索の隣接ノードが無い場合
    } else {
      dfsStack.pop();
      statusArray[researchingNode] = VISITED;
      nowTime++;
      f[researchingNode] = nowTime;
    }
  }
}

void dfs() {
  // 初期化
  for(int i = 0; i < n; i++) {
    statusArray[i] = 0;
  }

  // 未訪問のuを視点として深さ優先探索
  for(int u = 0; u < n; u++) {
    if(statusArray[u] == NOT_VISIT) {
      dfsVisit(u);
    }
  }

  for(int i = 0; i < n; i++) {
    cout << i+1 << " " << d[i] << " " << f[i] << endl;
  }
}


int main() {
  cin >> n;

  // 隣接行列の初期化
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  // 隣接ノードを調べる際に使用する配列の初期化
  for(int i = 0; i < n; i++) {
    nodeCountArray[i] = 0;
  }

  // 隣接行列に今回のグラフの状態を入れる
  int nodeId, degreeNum;
  for (int i = 0; i < n; i++) {
    cin >> nodeId >> degreeNum;

    // inputはNodeIdは1からスタートだが、扱いやすいよう0スタートにする(0オリジン)
    nodeId--;

    int adjacentNode;
    for (int j = 0; j < degreeNum; j++) {
      cin >> adjacentNode;
      // NodeIdと同じで扱いやすいよう0オリジンとする
      adjacentNode--;
      matrix[nodeId][adjacentNode] = 1;
    }
  }
  nowTime = 0;
  dfs();

  return 0;
}