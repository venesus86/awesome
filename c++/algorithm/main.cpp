#include "single_linked_list.hpp"

int main()
{
  single_list::slist<int> int_list1{1, 2, 3, 4};
  int_list1.print_all_data();
  single_list::slist<int> int_list2{int_list1};
  int_list2.insert_next(int_list2.get_node(2), 10);
  int_list2.print_all_data();
  return 0;
}