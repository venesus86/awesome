/*
input:
5
55 185
58 183
88 186
60 175
46 155

output:
2 2 1 2 5
*/

#include <iostream>

using namespace std;

int main()
{
  int count;
  cin >> count;

  struct Person {
    int weight;
    int height;
    int rank{1};
  };
  Person *person_list{new Person[count]};

  for (int idx{}; idx < count; ++idx)
    cin >> person_list[idx].weight >> person_list[idx].height;

  for (int idx{}; idx < count-1; ++idx) {
    for (int idx2{idx + 1}; idx2 < count; ++idx2) {
      if (person_list[idx].height > person_list[idx2].height && person_list[idx].weight > person_list[idx2].weight)
        ++person_list[idx2].rank;
      else if (person_list[idx].height < person_list[idx2].height && person_list[idx].weight < person_list[idx2].weight)
        ++person_list[idx].rank;
    }
  }

  for (int idx{}; idx < count; ++idx)
    cout << person_list[idx].rank << " ";

  delete[] person_list;
  return 0;
}