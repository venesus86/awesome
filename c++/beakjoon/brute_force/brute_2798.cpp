/*
블랙잭: 입력된 N개의 입력된 수 중 3개를 합한 결과가 입력된 X를 넘지 않는 가장 큰 수 구하기

ex> 입력된 5개의 숫자 (5 6 7 8 9)에서 세개 숫자의 합이 21을 넘지 않는 수 중에 가장 큰 수

input:
5 21
5 6 7 8 9

output:
21 (6 + 7 + 8)
*/

#include <iostream>

using namespace std;

int main()
{
  int card_count;
  int propose;

  cin >> card_count >> propose;
  int *card_set = new int[card_count];
  for (int idx{}; idx < card_count; ++idx)
    cin >> card_set[idx];
  
  int result{};
  for (int d1{}; d1 < card_count - 2; ++d1) {
    for (int d2{d1 + 1}; d2 < card_count - 1; ++d2) {
      for (int d3{d2 + 1}; d3 < card_count; ++d3) {
        int sum = card_set[d1] + card_set[d2] + card_set[d3];
        if (sum <= propose && sum > result)
          result = sum;
      }
    }
  }

  cout << result << endl;

  delete[] card_set;
  return 0;
}