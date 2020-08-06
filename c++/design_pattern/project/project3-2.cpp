/*
 2. 객체 어답터로 만들어 보세요.
*/

#include <iostream>
#include <list>

using namespace std;

template<typename DataType>
class Queue
{
    list<DataType> *l;
public:
    Queue() { l = new list<DataType>; }
    ~Queue() { delete l; }
    void Push(const DataType &d)
    {
        l->push_back(d);
    }

    DataType Pop()
    {
        DataType d = l->front();
        l->pop_front();
        return d;
    }
};

int main()
{
    Queue<int> q;
    q.Push(10);
    q.Push(20);
    cout << q.Pop() << endl; // 10
    cout << q.Pop() << endl; // 20
}