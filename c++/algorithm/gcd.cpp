/*
GDC(u, v) == GDC(u - v, v) ==  GDC(u % v, v) (u % v < v)
GDC(u, v) == GDC(v, u)
GDC(u, 0) == u
*/
#include <iostream>

using namespace std;

int get_gcd(int u, int v)
{
  while (v) {
    int t{u %= v};
    u = v;
    v = t;
  }
  return u;
}

int main()
{
  int u;
  int v;
  cout << "input two integer to get GCD" << endl;
  cin >>  u >> v ;
  cout << "result: " << get_gcd(u, v) << endl;
  return 0;
}