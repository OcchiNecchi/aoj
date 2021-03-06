// 8パズル
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <queue>
using namespace std;

const int N = 3;
const int N2 = 9;

struct Puzzle {
  int f[N2];
  int space;
  string path;

  bool operator < (const Puzzle &p) const {
    for(int i = 0; i < N2; i++) {
      if(f[i] == p.f[i]) continue;
      return f[i] > p.f[i];
    }
    return false;
  }
};

static const int dx[4] = {-1, 0, 1, 0};
static const int dy[4] = {0, -1, 0, 1};
static const char dir[4] = {'u', 'l', 'd', 'r'};

// パズルが並べられたか確認する
bool isTarget(Puzzle p) {
  for(int i = 0; i < N2; i++) {
    // 数字が順番に並んでいない場合=パズルが整列されていない場合はfalse
    if(p.f[i] != (i+1)) return false;
  }
  return true;
}

string bfs(Puzzle s) {
  queue<Puzzle> Q;

  // パズルがどう動いたのか状態を保持する
  map<Puzzle, bool> V;

  Puzzle u, v;
  s.path = "";
  Q.push(s);
  V[s] = true;

  while(!Q.empty()) {
    u = Q.front();
    Q.pop();
    if(isTarget(u)) return u.path;

    // パズルのスペースの座標を計算
    // x座標はN(3)でわる、yは3の余剰
    int sx = u.space / N;
    int sy = u.space % N;

    // パネルは１つだけ動かせる制約
    for(int r = 0; r < 4; r++) {
      // パネルを動かした後の位置
      int tx = sx + dx[r];
      int ty = sy + dy[r];

      // 動かせる位置ではない場合
      if(tx < 0 || ty < 0 || tx >= N || ty >= N) continue;
      
      v = u;
      swap(v.f[u.space], v.f[tx * N + ty]);
      v.space = tx * N + ty;

      // パズルの配置状態がまだ調べていないものだった場合
      if(!V[v]) {
        V[v] = true;
        v.path += dir[r];
        Q.push(v);
      }
    }
  }
  return "unsolvable";
}

int main() {
  Puzzle in;

  for(int i = 0; i < N2; i++) {
    cin >> in.f[i];
    if(in.f[i] == 0) {
      // set space
      in.f[i] = N2;
      in.space = i;
    }
  }
  string ans = bfs(in);
  cout << ans.size() << endl;
  return 0;
}
