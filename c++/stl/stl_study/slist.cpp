#include <iostream>

using namespace std;

/* stl find */
template <typename T1, typename T2>
T1 stl_find(T1 first, T1 last, T2 value)
{
    while (first != last && *first != value)
        ++first;
    
    return first;
}

template <typename T>
struct Node
{
    T data;
    Node* next;
    Node(const T& d, Node* n) : data(d), next(n) {}
};

template <typename T>
class slist_iterator
{
    Node<T>* current;

public:
    slist_iterator(Node<T> *p) : current(p) {}
    slist_iterator& operator++()
    {
        current = current->next;
        return *this;
    }
    slist_iterator operator++(int t)
    {
        slist_iterator temp{current};
        current = current->next;
        return temp;
    }
    T& operator*()
    {
        return current->data;
    }
    bool operator==(const slist_iterator &si)
    {
        return current == si.current;
    }
    bool operator!=(const slist_iterator &si)
    {
        return current != si.current;
    }
};

template <typename T>
class slist
{
    Node<T>* head = 0;
public:
    using iterator = slist_iterator<T>;
    iterator begin()
    {
        return iterator{head};
    }
    iterator end()
    {
        return iterator{0};
    }
    void push_front(const T &data)
    {
        head = new Node<T>{data, head};
    }
};

int main()
{
    slist<int> sl;
    sl.push_front(10);
    sl.push_front(20);
    sl.push_front(30);
    sl.push_front(40);
    sl.push_front(50);

    for (const auto &data : sl) {
        cout << data << endl;
    }
    /*
    slist<int>::iterator it = sl.begin();

    while (it != sl.end())
        cout << "data: " << *(it++) << endl;
    */
    slist<int>::iterator it = stl_find(sl.begin(), sl.end(), 20);
    if (it == sl.end())
        cout << "fail" << endl;
    else
        cout << "find data: " << *it << endl;
    return 0;
}