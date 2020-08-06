#include <iostream>
#include <set>
#include <string>

#define VERS (2)

using namespace std;

template <typename T, typename C = less<T>>
void print_set(const set<T, C> &s)
{
  for (const auto &elem : s)
    cout << elem << " " << endl;
}

class Todo
{
  int priority;
  string job_desc;

public:
  Todo() { cout << "Todo default constructor" << endl; }
  Todo(const Todo &t) : priority(t.priority), job_desc(t.job_desc) { cout << "Todo copy constructor" << endl; }
  Todo(int p, string desc) : priority(p), job_desc(desc) { cout << "Todo(int p, string desc) constructor" << endl; }
  Todo(const initializer_list<Todo> &list)
  {
    cout << "Todo initializer_list constructor" << endl;
    for (auto list_it{list.begin()}; list_it < list.end(); ++list_it)
      cout << *list_it << endl;
  }
  ~Todo() { cout << "Todo destructor" << endl; }

#if VERS == 1
  bool operator<(const Todo &t) const
  {
    if (priority == t.priority)
      return job_desc < t.job_desc;
    return priority > t.priority;
  }
#else
  friend struct TodoCmp;
#endif
  friend ostream& operator<<(ostream &o, const Todo &t);
};

#if VERS == 2
struct TodoCmp {
  bool operator()(const Todo &t1, const Todo t2)
  {
    if (t1.priority == t2.priority)
      return t1.job_desc < t2.job_desc;
    return t1.priority > t2.priority;
  }
};
#endif

ostream& operator<<(ostream &o, const Todo &t)
{
  o << "priority: " << t.priority << ", job_desc: " << t.job_desc;
  return o;
}

int main()
{
#if VERS == 1
  set<Todo> todo_set;
#else
  set<Todo, TodoCmp> todo_set;
#endif
  todo_set.insert(Todo(1, "농구 하기"));
  todo_set.insert(Todo(2, "수학 숙제 하기"));
  todo_set.insert(Todo(1, "프로그래밍 프로젝트"));
  todo_set.insert(Todo(3, "친구 만나기"));
  todo_set.insert(Todo(2, "영화 보기"));

  print_set(todo_set);

#if CONSTRUCT_TEST
  cout << "test1()" << endl;
  Todo test1();
  cout << "test2" << endl;
  Todo test2;
  cout << "test3{}" << endl;
  Todo test3{};
  cout << "test4{{1, \"농구 하기\"}}" << endl;
  Todo test4{{1, "농구 하기"}};
  cout << "test5{1, \"농구 하기\"}" << endl;
  Todo test5{1, "농구 하기"};
#endif

  return 0;
}