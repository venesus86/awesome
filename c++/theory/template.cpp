#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cinttypes>

using std::cout;
using std::endl;
using std::string;

template <typename T>
class Vector
{
  T *data;
  int capacity;
  int length;

public:
  Vector(int n = 1) : data(new T[n]), capacity(n), length(0) { cout << "constructor Vector" << endl; }
  /* initializer list */
  Vector(std::initializer_list<T> list) : length(list.size()), data(new T[length]), capacity(length)
  {
    cout << "initializer list" << endl;
    int count = 0;
    for (auto it{list.begin()}; it < list.end(); ++it)
    {
      data[count++] = *it;
    }
  }
  /* initializer list */

  void push_back(T d)
  {
    if (length >= capacity)
    {
      capacity *= 2;
      T *tmp_data = new T[capacity]();
      for (int idx = 0; idx < length; ++idx)
        tmp_data[idx] = data[idx];
      delete[] data;
      data = tmp_data;
    }
    this->data[length] = d;
    ++length;
  }

  void remove(int idx)
  {
    if (idx < 0 || idx >= length)
      return;

    for (int i = idx + 1; i < length; ++i)
      data[i - 1] = data[i];
    --length;
  }

  T operator[](int idx)
  {
    if (idx >= 0 && idx < length)
      return data[idx];
    else
      return T();
  }

  int size() { return length; }

  void swap(int a, int b)
  {
    if (a < 0 || a >= length || b < 0 || b >= length)
      return;

    T tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
  }

  void print_vector_data()
  {
    cout << "capacity: " << capacity << ", length: " << length << endl;
    cout << "check data list" << endl;
    for (int idx = 0; idx < length; ++idx)
      cout << idx << "> " << data[idx] << endl;
  }

  ~Vector()
  {
    delete[] data;
    cout << "destructor Vector" << endl;
  }
};

template <typename Cont>
void bubble_sort(Cont &cont)
{
  for (int i = 0; i < cont.size(); i++)
    for (int j = i + 1; j < cont.size(); j++)
      if (cont[i] > cont[j])
        cont.swap(i, j);
}

/* functor */
template <typename Cont, typename Comp>
void bubble_sort(Cont &cont, Comp &comp)
{
  for (int i = 0; i < cont.size(); ++i)
    for (int j = i + 1; j < cont.size(); ++j)
      if (!comp(cont[i], cont[j]))
        cont.swap(i, j);
}

template <typename T>
struct Comp_increase
{
  bool operator()(T a, T b)
  {
    return a < b;
  }
};

template <typename T>
struct Comp_decrease
{
  bool operator()(T a, T b)
  {
    return a > b;
  }
};
/* functor */

/* variable parameter function */
template <typename T>
void print_args(T data)
{
  cout << data << endl;
}

template <typename T, typename... Types>
void print_args(T arg, Types... args)
{
  cout << arg << ", ";
  print_args(args...);
}

size_t get_str_size(const char *str)
{
  return str ? strlen(str) : 0;
}

size_t get_str_size(const string &str)
{
  return str.size();
}

template <typename String, typename... Strings>
size_t get_str_size(String str, Strings... strs)
{
  return get_str_size(str) + get_str_size(strs...);
}

template <typename String>
string str_cat(String str)
{
  return string(str);
}

void append_str(string *result_str)
{
  return;
}

template <typename String, typename... Strings>
void append_str(string *result_str, const String &str, Strings... strs)
{
  result_str->append(str);
  append_str(result_str, strs...);
}

template <typename String, typename... Strings>
string str_cat(const String &str, Strings... strs)
{
  string total_str;
  total_str.reserve(get_str_size(str, strs...));
  total_str = str;
  append_str(&total_str, strs...);
  return total_str;
}

template <typename Int, typename... Ints>
Int sum_all(Int start, Ints... numbers)
{
  return (start + ... + numbers);
}

template <typename Int, typename... Ints>
Int diff_from(Int start, Ints... nums) {
  return (start - ... - nums);
}

template <typename T>
class Test
{
public:
  Test() { cout << "Test constructor" << endl; }
  void print(T t) { cout << "t: " << t << endl;}
};

template <typename T, typename... Data>
void do_many_things(T t, Data... data)
{
  (t.print(data), ...);
}
/* variable factor function */

int main()
{
  {
    Vector<int> int_v(2);
    int_v.push_back(3);
    int_v.push_back(6);
    int_v.push_back(1);
    int_v.push_back(10);
    int_v.push_back(4);
    int_v.print_vector_data();
    Comp_increase<int> c_inc;
    bubble_sort(int_v, c_inc);
    int_v.print_vector_data();
    Comp_decrease<int> c_dec;
    bubble_sort(int_v, c_dec);
    int_v.print_vector_data();
  }

  {
    Vector<string> str_v;
    str_v.print_vector_data();
    str_v.push_back("test3");
    str_v.push_back("test1");
    str_v.push_back("test4");
    str_v.push_back("test2");
    str_v.print_vector_data();
    str_v.print_vector_data();
    Comp_increase<string> str_inc;
    bubble_sort(str_v, str_inc);
    str_v.print_vector_data();
    Comp_decrease<string> str_dec;
    bubble_sort(str_v, str_dec);
    str_v.print_vector_data();
  }

  {
    Vector<int> int2_v{10, 14, 55, 20, 3};
    int2_v.print_vector_data();
  }

  {
    print_args(1, 2, 3, 4, "test");
  }

  {
    string str = str_cat("this", " is", " test", " string", "!!!!");
    string str2 = str_cat("this", " is", " test");
    cout << str << endl;
    cout << str2 << endl;
  }

  {
    uint64_t test = UINT64_MAX;
    printf("test: %" PRIu64 "\n", test);
  }

  {
    cout << "sum_all: " << sum_all(1, 2, 3, 4, 5) << endl;
    cout << "diff_from: " << diff_from(100, 1, 2, 3, 4, 5) << endl;
  }

  {
    Test<int> t;
    do_many_things(t, 1, 2, 3, 4, 5);
  }

  return 0;
}