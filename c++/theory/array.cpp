#include <iostream>

using namespace std;

void print_array(int *a, int n1, int n2)
{
  for (int i{}; i < n1; ++i) {
    for (int j{}; j < n2; ++j) {
      cout << "array[" << i << "][" << j << "]: " << a[i * n2 + j] << endl;
    }
  }
}

void print_array(int *a, int n1, int n2, int n3)
{
  cout << "print_array(int *a, int n1, int n2, int n3)" << endl;
  for (int i{}; i < n1; ++i) {
    for (int j{}; j < n2; ++j) {
      for (int k{}; k < n3; ++k)
        cout << "array[" << i << "][" << j << "][" << k << "]: " << a[i * n2 * n3 + j * n3 + k] << endl;
    }
  }
}

void print_array(int a[][3][3], int n1, int n2, int n3)
{
  cout << "print_array(int a[][3][3], int n1, int n2, int n3)" << endl;
  for (int i{}; i < n1; ++i) {
    for (int j{}; j < n2; ++j) {
      for (int k{}; k < n3; ++k)
        cout << "array[" << i << "][" << j << "][" << k << "]: " << a[i][j][k] << endl;
    }
  }
}

int main()
{
  int a[3]{1,2,3};
  int b[3][3]{{1,2,3},{4,5,6},{7,8,9}};
  int c[3][3][3]{{{1,2,3},{4,5,6},{7,8,9}},{{1,2,3},{4,5,6},{7,8,9}},{{1,2,3},{4,5,6},{7,8,9}}};
  print_array(b[0], 3, 3);
  print_array(c[0][0], 3, 3, 3);
  print_array(c, 3, 3, 3);
  
  return 0;
}