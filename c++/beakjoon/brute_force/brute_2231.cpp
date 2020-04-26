// 첫째 줄에 자연수 N(1 ≤ N ≤ 1,000,000)이 주어진다.
// 입력: 216 / 출력: 198

#include <iostream>

using namespace std;

int calc(int num)
{
  int result{num};
  do {
    result += num % 10;
    num /= 10;
  } while (num);

  return result;
}

int main()
{
  int input_num;
  cin >> input_num;

  int token{1};
  int input_digit{};
  int max_count{};
  do {
    ++input_digit;
    token *= 10;
  } while (input_num / token);

  int result = input_num;
  for (int idx{input_num - 9 * input_digit}; idx < input_num; ++idx) {
    int temp{calc(idx)};
    if (temp == input_num && idx < result)
      result = idx;
  }

  if (result == input_num)
    result = 0;
  cout << result << endl;

  return 0;
}