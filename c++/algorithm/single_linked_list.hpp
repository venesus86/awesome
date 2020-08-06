#include <iostream>

using std::cout;
using std::endl;
using std::initializer_list;

namespace single_list
{
template <typename T>
class slist
{
public:
  struct Node
  {
    T data;
    Node *next;
  };
  slist() : m_head(new Node{}), m_tail(new Node{}), m_count(0)
  {
    cout << __func__ << "() called" << endl;
    m_head->next = m_tail;
    m_tail->next = m_tail;
  }

  slist(const slist &list) : slist()
  {
    cout << __func__ << "(const slist &list) called" << endl;
    Node *src_node{list.m_head->next};
    Node *dst_node{m_head};
    while (src_node != list.m_tail)
    {
      dst_node = insert_next(dst_node, src_node->data);
      src_node = src_node->next;
      ++m_count;
    }
  }

  slist(const initializer_list<T> &list) : slist()
  {
    cout << __func__ << "(const initializer_list<T> &list) called" << endl;
    Node *dst_node{m_head};
    for (const auto &l : list)
    {
      dst_node = insert_next(dst_node, l);
      ++m_count;
    }
  }

  ~slist()
  {
    cout << __func__ << " called" << endl;
    Node *node{m_head};
    while (node->next != m_tail)
      delete_next(node);
    delete m_head;
    delete m_tail;
  }

  Node *insert_next(Node *pos, T new_data)
  {
    cout << __func__ << " called: " << new_data << endl;
    if (!pos || pos == m_tail)
      return nullptr;
    Node *new_node{new Node{new_data, pos->next}};
    pos->next = new_node;
    return new_node;
  }

  Node *delete_next(Node *pos)
  {
    cout << __func__ << " called" << endl;
    if (!pos || pos->next == m_tail)
      return nullptr;
    Node *delete_node{pos->next};
    pos->next = delete_node->next;
    delete delete_node;
    --m_count;
    return pos;
  }

  Node *get_node(int pos) const
  {
    if (pos >= m_count || pos < 0)
      return nullptr;
    Node *node{m_head};
    for (int idx{}; idx <= pos; ++idx)
      node = node->next;
    return node;
  }

  void print_all_data(void) const
  {
    cout << __func__ << " called" << endl;
    Node *node{m_head};
    cout << "m_count: " << m_count << endl;
    while ((node = node->next) != m_tail)
      cout << "[ data: " << node->data << " ]" << endl;
  }

private:
  Node *m_head;
  Node *m_tail;
  int m_count;
};
}

// int main()
// {
//   slist<int> int_list1{1, 2, 3, 4};
//   int_list1.print_all_data();
//   slist<int> int_list2{int_list1};
//   int_list2.insert_next(int_list2.get_node(2), 10);
//   int_list2.print_all_data();
//   return 0;
//}