#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
  int number;
  cout << "input number: ";
  cin >> number;
  if (number < 2) {
    cout << "input number must larger than 1 (input: " << number << ")" << endl;
    return -1;
  }
  int *num_array{new int[number + 1]{}};
  for (int num{2}; num <= number; ++num) {
    if (num_array[num] == 1)
      continue;
    num_array[num] = num;
    for (int count{num * 2 - 2}; count <= number; count += num)
      num_array[count] = 1;
  }

  cout << "result: [ ";
  for (int idx{2}; idx <= number; ++idx)
    if (num_array[idx] != 1)
      cout << num_array[idx] << " ";
  cout << "]" << endl;
  
  delete[] num_array;
  return 0;
}