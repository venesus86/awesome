/*
White, Black이 반복되는 체스판 만들기
첫째 줄에 지민이가 다시 칠해야 하는 정사각형 개수의 최솟값을 출력한다.

input:      
10 13
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
BBBBBBBBWBWBW
BBBBBBBBBWBWB
WWWWWWWWWWBWB
WWWWWWWWWWBWB

output:
12

반례:
8 8
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBBBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW

8 8
BBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
WBWBWBWB
BWBWBWBW
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int row;
  int col;
  cin >> row >> col;
  vector<vector<char>> data(row, vector<char>(col, 0));
  for (int idx{}; idx < row * col; ++idx)
    cin >> data[idx/col][idx%col];
  
  const int base_size{8};
  int result{base_size *base_size};
  const char col_start_color_w{'W'};
  const char col_start_color_b{'B'};
  for (int row_idx1{}; row_idx1 < row - (base_size - 1); ++row_idx1) {
    for (int col_idx1{}; col_idx1 < col - (base_size - 1); ++col_idx1) {
      int temp_result_w{};
      int temp_result_b{};
      for (int row_idx2{row_idx1}; row_idx2 < row_idx1 + base_size; ++row_idx2) {
        char temp_col_start_color_w{col_start_color_w};
        char temp_col_start_color_b{col_start_color_b};
        if (row_idx2 % 2 == row_idx1 % 2) {
          if (col_start_color_w != data[row_idx2][col_idx1])
            ++temp_result_w;
          if (col_start_color_b != data[row_idx2][col_idx1])
            ++temp_result_b;
        } else {
          temp_col_start_color_w = 'B';
          temp_col_start_color_b = 'W';
          if (col_start_color_w == data[row_idx2][col_idx1])
            ++temp_result_w;
          if (col_start_color_b == data[row_idx2][col_idx1])
            ++temp_result_b;
        }
        for (int col_idx2{col_idx1 + 1}; col_idx2 < col_idx1 + base_size; ++col_idx2) {
          if (col_idx2 % 2 == col_idx1 % 2) {
            if (data[row_idx2][col_idx2] != temp_col_start_color_w)
              ++temp_result_w;
            if (data[row_idx2][col_idx2] != temp_col_start_color_b)
              ++temp_result_b;
          } else {
            if (data[row_idx2][col_idx2] == temp_col_start_color_w)
              ++temp_result_w;
            if (data[row_idx2][col_idx2] == temp_col_start_color_b)
              ++temp_result_b;
          }
        }
      }
      int min_temp_result{(temp_result_w < temp_result_b)? temp_result_w: temp_result_b};
      if (min_temp_result < result)
        result = min_temp_result;
    }
  }

  cout << result << endl;

  return 0;
}