#include <iostream>
#include <vector>
#include <array>
#include <cstdint>

using namespace std;

#define DEQUEUE_BLOCK_SIZE (5)

template <typename T>
class Dequeue
{
  using BLOCK = vector<T>;
  BLOCK *start_block{}, *last_block{};
  typename BLOCK::iterator begin{}, end{};
  vector<BLOCK> table{};
public:
  Dequeue() { cout << "Dequeue default Constructor!" << endl; }
  Dequeue(initializer_list<T> &list)
  {
    cout << "Dequeue initializer Constructor!" << endl;
    for (typename initializer_list<T>::size_type list_idx{}; list_idx < list.size(); ++list_idx) {
      if (!begin) {
        array<T, DEQUEUE_BLOCK_SIZE> block{};
        for (int idx{}; idx < DEQUEUE_BLOCK_SIZE; ++idx)
          block[idx] = list_it[list_idx];
      } else if (!end) {
        ;
      }
    }
  }
  ~Dequeue() { cout << "Dequeue Destructor!" << endl; }

  void push_back(const T &t)
  {
    if (table.empty() || table.end()->size() == table.end()->max_size()) {
        table.push_back({t});
      } else {
        *(table.end()->end()) = t;
      }
  }

  void push_front(const T &t)
  {
    if (table.empty() || *(table.begin()->rend() - 1) == &(table.begin()->front())) {
        BLOCK block{};
        block.back() = t;
        table.push_front(black);
      } else {
        *(table.begin()->end()) = t;
      }
  }

  void print_all_data()
  {
    cout << "print all data" << endl;
    // for (const auto table_it{table.begin()}; table_it < table.end(); ++table_it) {
      
    // }
    for (const auto &table_data : table) {
      cout << "[ ";
      for (const auto &block_data : table_data) {
        cout << block_data << ", " << endl;
      }
      cout << "]" << endl;
    }
  }
};

int main()
{
  Dequeue<int> dq;
  return 0;
}