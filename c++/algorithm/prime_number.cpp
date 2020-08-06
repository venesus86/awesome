#include <iostream>
#include <cmath>

using namespace std;

bool check_prime_number(int number)
{
  int sqrt_num{static_cast<int>(sqrt(number))};
  for (int num{2}; num <= sqrt_num; ++num) {
    if (!(number % num))
      return false;
  }
  return true;
}

int main()
{
  int number;
  cout << "input number: ";
  cin >> number;
  cout << "result: " << check_prime_number(number) << endl;

  return 0;
}