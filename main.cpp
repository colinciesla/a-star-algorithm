#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::abs;
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State {
  kEmpty,
  kObstacle,
  kClosed,
  kPath,
  kStart,
  kFinish
};

constexpr int delta[4][2] {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<State> ParseLine(const string &line) {
  istringstream stringStream(line);
  int n;
  char c;
  vector<State> row;
  while (stringStream >> n >> c && c == ',') {
    if (n == 0) {
      row.push_back(State::kEmpty);
    } else {
      row.push_back(State::kObstacle);
    }
  }
  return row;
}

vector<vector<State>> ReadBoardFile(const string &path) {
  ifstream file(path);
  vector<vector<State>> board {};
  if (file) {
    string line;
    while (getline(file, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

int Heuristic(const int x1, const int y1, const int x2, const int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen(const int x,
               const int y,
               const int g,
               const int h,
               vector<vector<int>> &openNodes,
               vector<vector<State>> &board) {
  const vector node = {x, y, g, h};

  openNodes.push_back(node);

  board[x][y] = State::kClosed;
}

string CellString(const State cell) {
  switch (cell) {
    case State::kObstacle:
      return "⛰️   ";
    case State::kPath:
      return "🚗   ";
    case State::kStart:
      return "🚦   ";
    case State::kFinish:
      return "🏁   ";
    default:
      return "0   ";
  }
}

void PrintBoard(const vector<vector<State>> &board) {
  for (const auto &i : board) {
    for (const auto j : i) {
      cout << CellString(j);
    }
    cout << "\n";
  }
}

bool Compare(const vector<int> &a, const vector<int> &b) {
  return a[2] + a[3] > b[2] + b[3];
}

void CellSort(vector<vector<int>>* v) {
  sort(v->begin(), v->end(), Compare);
}

bool CheckValidCell(const int x, const int y, const vector<vector<State>> &grid) {
  if (const auto [xOnGrid, yOnGrid] =
        std::pair {x >= 0 && x < grid.size(), y >= 0 && y < grid[0].size()};
      xOnGrid && yOnGrid) {
    return grid[x][y] == State::kEmpty;
  }

  return false;
}

void ExpandNeighbors(const vector<int> &current,
                     const int goal[2],
                     vector<vector<int>> &openNodes,
                     vector<vector<State>> &grid) {
  const int x = current[0];
  const int y = current[1];
  const int g = current[2];

  for (const auto i : delta) {
    if (auto [x2, y2] = std::pair {x + i[0], y + i[1]}; CheckValidCell(x2, y2, grid)) {
      const int g2 = g + 1;
      const int h2 = Heuristic(x2, y2, goal[0], goal[1]);

      AddToOpen(x2, y2, g2, h2, openNodes, grid);
    }
  }
}

vector<vector<State>> Search(vector<vector<State>> &board, const int init[], const int goal[]) {
  vector<vector<int>> open {};

  const int x = init[0];
  const int y = init[1];
  constexpr int g = 0;
  const int h = Heuristic(x, y, goal[0], goal[1]);

  AddToOpen(x, y, g, h, open, board);

  while (!open.empty()) {
    CellSort(&open);

    const vector<int> currentNode = open.back();
    open.pop_back();

    board[currentNode[0]][currentNode[1]] = State::kPath;

    if (currentNode[0] == goal[0] && currentNode[1] == goal[1]) {
      board[init[0]][init[1]] = State::kStart;
      board[goal[0]][goal[1]] = State::kFinish;

      return board;
    }

    ExpandNeighbors(currentNode, goal, open, board);
  }

  cout << "No path found!" << "\n";

  return vector<vector<State>> {};
}

#include "test.cpp"

int main() {
  constexpr int init[2] = {0, 0};
  constexpr int goal[2] = {4, 5};
  auto board = ReadBoardFile("1.board");
  const vector<vector<State>> solution = Search(board, init, goal);

  PrintBoard(solution);

  TestHeuristic();
  TestAddToOpen();
  TestCompare();
  TestSearch();
  TestCheckValidCell();
  TestExpandNeighbors();
}
