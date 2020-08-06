#include <iostream>

using namespace std;

template <typename T, unsigned int N>
class Array
{
  T data[N];

public:
  Array() { cout << "default Array constructor" << endl; }
  Array(T (&arr)[N])
  {
    cout << "T (&arr)[N] Array constructor" << endl;
    for (unsigned int idx = 0; idx < N; ++idx)
      data[idx] = arr[idx];
  }
  Array(initializer_list<T> list)
  {
    cout << "initializer list Array constructor" << endl;
    int idx = 0;
    for (auto it{list.begin()}; it < list.end(); ++it)
      data[idx++] = *it;
  }
  
  T* get_array() { return data; }
  unsigned int size() { return N; }

  T operator[](unsigned int idx)
  {
    return (idx < N) ? data[idx] : T();
  }

  void print_array()
  {
    for (unsigned int idx = 0; idx < N; ++idx)
      cout << "data[" << idx << "]: " << data[idx] << endl;
  }
};

int main()
{
  Array<int, 1> int_array0{};
  int a[3]{10, 20, 30};
  Array<int, 3> int_array1{a};
  int_array1.print_array();
  Array<int, 5> int_array2{1, 2, 3, 4, 5};
  int_array2.print_array();

  return 0;
}