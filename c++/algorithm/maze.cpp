#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#define MAZE_SIZE (19)
#define MAZE_START_IDX (17)
#define MSEC (1000)
#define DRAW_SPEED (50 * MSEC)

using namespace std;

enum direction {
  UP = 1,
  RIGHT = 2,
  DOWN = 4,
  LEFT = 8
};

int maze[MAZE_SIZE][MAZE_SIZE]{
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
  { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int path_idx;
int path[MAZE_SIZE * MAZE_SIZE]{-1};

/*
우선법(right hand on wall): 오른손을 벽에 대고 간다고 가정한다
psuedo code:
up: 1 / right: 2 / down: 4 / left: 8

while(still in maze) {
  turn right;
  while(wall ahead) {
    turn left;
  }
  go forward;
}
*/
void draw_maze(int maze_data[][MAZE_SIZE], int max_size, int x, int y)
{
  cout << string( 100, '\n' );
  for (int row{}; row < max_size; ++row) {
    for (int col{}; col < max_size; ++col) {
      if (row == y && col == x)
        cout << "ㅅ";
      else if (maze_data[row][col] == 0)
        cout << "  ";
      else
        cout << "ㅁ";
    }
    cout << endl;
  }
  usleep(DRAW_SPEED);
}

void clear_record_path()
{
  path_idx = 0;
  path[0] = -1;
}

void record_path(int x, int y)
{
  path[path_idx++] = x;
  path[path_idx++] = y;
}

void print_record_path()
{
  cout << "print path:" << endl;
  for (int idx{}; idx < path_idx;) {
    cout << "(" << path[idx++] << ", " << path[idx++] << ") ";
    if (idx % 20 == 0)
      cout << endl;
  }
  if (path_idx % 20)
    cout << endl;
}

void delete_path(int start_idx, int end_idx)
{
  if (start_idx >= path_idx || end_idx >= path_idx || start_idx >= end_idx)
    return;
  int idx{};
  while (end_idx + idx < path_idx) {
    ++idx;
    path[start_idx + idx] = path[end_idx + idx];
  }
  path_idx -= end_idx - start_idx;
}

void get_shortest_path()
{
  for (int idx{}; idx < path_idx; idx += 2)
    for (int check_idx{idx + 2}; check_idx < path_idx; check_idx += 2)
      if (path[idx] == path[check_idx] && path[idx + 1] == path[check_idx + 1])
        delete_path(idx, check_idx);
}

void draw_shortest_path()
{
  get_shortest_path();
  for (int idx{}; idx < path_idx; idx += 2) {
    draw_maze(maze, MAZE_SIZE, path[idx], path[idx + 1]);
  }
}

/* go forward */
void go_forward(int &x, int &y, int dir)
{
  switch (dir) {
    case UP:
      --y;
      break;
    case RIGHT:
      ++x;
      break;
    case DOWN:
      ++y;
      break;
    case LEFT:
      --x;
      break;
    default:
      cout << "dir is wrong: " << dir << endl;
      break;
  }
}

bool still_in_maze(int x, int y)
{
  if (x <= 0 || x >= MAZE_SIZE || y <= 0 || y >= MAZE_SIZE)
    return false;
  return true;
}

bool check_wall_ahead(int x, int y, int dir)
{
  switch (dir) {
    case UP:
      --y;
      break;
    case RIGHT:
      ++x;
      break;
    case DOWN:
      ++y;
      break;
    case LEFT:
      --x;
      break;
    default:
      cout << "dir is wrong: " << dir << endl;
      break;
  }
  return (maze[y][x] == 1);
}

void turn_right(int &dir)
{
  dir <<= 1;
  if (dir > LEFT)
    dir = UP;
}

void turn_left(int &dir)
{
  dir >>= 1;
  if (dir < UP)
    dir = LEFT;
}

int right_hand_on_wall(int x, int y, int dir)
{
  int length = 0;
  clear_record_path();
  record_path(x, y);
  draw_maze(maze, MAZE_SIZE, x, y);
  while (still_in_maze(x, y)) {
    turn_right(dir);
    while (check_wall_ahead(x, y, dir))
      turn_left(dir);
    go_forward(x, y, dir);
    record_path(x, y);
    draw_maze(maze, MAZE_SIZE, x, y);
    ++length;
  }
  print_record_path();
  cout << "right hand length: " << length << endl;
  usleep(1000*MSEC);
  cout << string( 100, '\n' );
  cout << "draw shortest path" << endl;
  usleep(1000*MSEC);
  draw_shortest_path();
  return path_idx / 2;
}

int left_hand_on_wall(int x, int y, int dir)
{
  int length = 0;
  clear_record_path();
  record_path(x, y);
  draw_maze(maze, MAZE_SIZE, x, y);
  while (still_in_maze(x, y)) {
    turn_left(dir);
    while (check_wall_ahead(x, y, dir))
      turn_right(dir);
    go_forward(x, y, dir);
    record_path(x, y);
    draw_maze(maze, MAZE_SIZE, x, y);
    ++length;
  }
  print_record_path();
  cout << "left hand length: " << length << endl;
  usleep(1000*MSEC);
  //cout << string( 100, '\n' );
  cout << "draw shortest path" << endl;
  usleep(1000*MSEC);
  draw_shortest_path();
  return path_idx / 2;
}

int main()
{
  int x{MAZE_START_IDX};
  int y{MAZE_START_IDX};
  int dir{UP};
  int right_length{right_hand_on_wall(x, y, dir)};
  usleep(3000*MSEC);
  int left_length{left_hand_on_wall(x, y, dir)};

  cout << "shortest right hand length: " << right_length << endl;
  cout << "shortest left hand length: " << left_length << endl;
  cout << "finish maze!!" << endl;

  return 0;
}