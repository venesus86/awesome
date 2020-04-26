/* 5 21
5 6 7 8 9 */

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